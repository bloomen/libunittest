#include <libunittest/argparser.hpp>

namespace unittest {
namespace core {


argparser::argparser()
		: command_line_(), app_name_(), args_(), registry_(),
		  ordered_registry_()
{
	register_trigger('h', "", "Displays this help message and exits", false);
}

argparser::~argparser()
{}

std::string
argparser::command_line() const
{
	return command_line_;
}


std::string
argparser::make_arg_string(char arg)
{
	return join('-', arg);
}

void
argparser::check_already_registered(char argument)
{
    if (registry_.find(argument)!=registry_.end())
        throw std::invalid_argument(join("Argument already registered: ", argument));
}

void
argparser::register_trigger(char argument,
							std::string value_name,
							std::string description,
							bool default_value)
{
	check_already_registered(argument);
	registry_[argument] = {registry_.size(), true, value_name, value_name, description, join(default_value), make_repr(default_value), false};
}

void
argparser::write_help(std::ostream& stream)
{
	const auto desc = description();
	if (desc.size()) stream << desc << "\n\n";
    stream << "Usage: " << app_name_ << " ";
    for (auto& row : ordered_registry_) {
    	if (row.second.required) {
    		stream << make_arg_string(row.first) << " " << row.second.value_name << " ";
    	}
    }
    stream << "[Arguments]\n\n";
    stream << "Arguments:\n";
    for (auto& row : ordered_registry_) {
    	std::string appendix;
		if (row.second.required)
			appendix = " (required)";
		else if (!row.second.is_trigger)
			appendix = " (default: " + row.second.default_value + ")";
		std::string value_name = row.second.long_value_name;
		if (row.second.is_trigger)
			value_name = std::string(value_name.size(), ' ');
    	stream << make_arg_string(row.first) << " " << value_name << "  " << row.second.description << appendix << std::endl;
    }
    stream << std::flush;
}

void
argparser::error(const std::string& message)
{
    std::ostringstream stream;
    write_help(stream);
    throw argparser_error(join(message, "\n\n", stream.str()));
}

std::vector<std::string>
argparser::expand_arguments(int argc, char **argv)
{
    std::vector<std::string> arguments;
    arguments.reserve(argc - 1);
    const std::string prefix = "--";
    for (int i=1; i<argc; ++i) {
        arguments.push_back(argv[i]);
        if (arguments.back().substr(0, prefix.size())==prefix) {
            error("Only options with a single '-' are supported");
        }
    }
    return argparser::expand_commandline_arguments(arguments);
}

argparser::argrow
argparser::get_argrow(char argument)
{
	argrow row;
	try {
		row = registry_.at(argument);
	} catch (const std::out_of_range&) {
		throw std::out_of_range(join("Asking for unregistered argument: ", argument));
	}
	return row;
}

template<>
void
argparser::assign_value<bool>(bool& result,
					    	  char argument)
{
	const auto row = get_argrow(argument);
	const std::string flag = make_arg_string(argument);
	result = get_value<bool>(flag, row.default_value);
	for (size_t i=0; i<args_.size(); ++i) {
		if (args_[i]==flag) {
			result = !result;
    		registry_[argument].representation = make_repr(result);
			args_.erase(args_.begin()+i);
		}
	}
}

template<>
std::string
argparser::get_value<std::string>(std::string,
				     	 	 	  std::string value)
{
	return value;
}

template<>
std::string
argparser::make_repr<bool>(bool value)
{
	return value ? "true" : "false";
}

template<>
std::string
argparser::make_repr<std::string>(std::string value)
{
	return join("'", value, "'");
}

void
argparser::parse(int argc, char **argv)
{
	for (int i=0; i<argc; ++i) {
		command_line_ += std::string(argv[i]);
		if (i<argc-1) command_line_ += " ";
	}
	register_arguments();
    app_name_ = argv[0];
    args_ = expand_arguments(argc, argv);
	size_t max_length = 0;
	ordered_registry_ = std::vector<std::pair<char,argrow>>(registry_.size());
    for (auto row : registry_) {
    	ordered_registry_[row.second.index] = std::make_pair(row.first, row.second);
    	if (row.second.value_name.length() > max_length) {
    		max_length = row.second.value_name.length();
    	}
    }
    for (auto& row : ordered_registry_) {
		row.second.long_value_name += std::string(max_length - row.second.value_name.length(), ' ');
    }
    bool help;
    assign_value(help, 'h');
	if (help) {
		write_help(std::cout);
		std::exit(EXIT_SUCCESS);
	}
    assign_values();
    if (args_.size()!=0) {
    	error(join("No such argument: '", args_[0], "'"));
    }
    check_values();
    for (auto row : registry_) {
    	ordered_registry_[row.second.index].second.representation = row.second.representation;
    }
}

std::vector<std::string>
argparser::expand_commandline_arguments(const std::vector<std::string>& arguments)
{
    const char flag = '-';
    const std::string sflag(1, flag);
    std::vector<std::string> args;
    for (auto& value : arguments) {
        if (value.substr(0, 1)==sflag) {
            const std::string expanded(value.substr(1, value.size()));
            for (auto& val : expanded) {
                if (val != flag)
                    args.push_back(join(flag, val));
            }
        } else {
            args.push_back(value);
        }
    }
    return args;
}

std::ostream&
operator<<(std::ostream& os, const argparser& obj)
{
    for (auto& row : obj.ordered_registry_) {
    	if (row.second.value_name.size()) {
    		os << row.second.long_value_name << " = " << row.second.representation << std::endl;
    	}
    }
    os << std::flush;
    return os;
}

argparser::argrow::argrow()
	: index(0), is_trigger(false), value_name(),
	  long_value_name(), description(),
	  default_value(), representation(),
	  required(false)
{}

argparser::argrow::argrow(size_t index,
                  	  	  bool is_trigger,
                  	  	  std::string value_name,
                  	  	  std::string long_value_name,
                  	  	  std::string description,
                  	  	  std::string default_value,
                  	  	  std::string representation,
                  	  	  bool required)
	: index(index), is_trigger(is_trigger), value_name(value_name),
	  long_value_name(long_value_name), description(description),
	  default_value(default_value), representation(representation),
	  required(required)
{}


argparser_error::argparser_error(const std::string& message)
    : std::runtime_error(message)
{}

argparser_error::~argparser_error() noexcept
{}


} // core
} // unittest
