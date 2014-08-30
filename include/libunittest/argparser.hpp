/**
 * @brief An argument parser
 * @file argparser.hpp
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <libunittest/utilities.hpp>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief An argument parser
 */
class argparser {
public:
	/**
	 * @brief Destructor
	 */
	virtual ~argparser();
	/**
	 * @brief Parses the arguments
	 * @param argc The number of arguments
	 * @param argv The array of arguments
	 */
	void
	parse(int argc, char **argv);
	/**
	 * Returns the command line
	 * @return The command line
	 */
	std::string
	command_line() const;

private:
	/**
	 * @brief Override this to provide a helpful command description
	 * @return The command description
	 */
	virtual std::string
    description() { return ""; }
	/**
	 * @brief Override this to register arguments through protected methods:
	 * 	register_argument() and register_trigger()
	 */
    virtual void
    register_arguments() {}
    /**
     * @brief Override this to assign values to variables through protected
     * 	method: assign_value()
     */
    virtual void
    assign_values() {}
    /**
     * @brief Override this to check the assigned values
     */
    virtual void
    check_values() {}

protected:
    /**
     * @brief Constructor
     */
	argparser();
	/**
	 * @brief Registers an argument
	 * @param argument The argument flag
	 * @param value_name The name of the argument
	 * @param description A description
	 * @param default_value The default value
	 * @param required Whether this argument is required
	 */
	template<typename T>
	void
	register_argument(char argument,
					  std::string value_name,
					  std::string description,
					  T default_value,
					  bool required=false)
	{
		check_already_registered(argument);
		registry_[argument] = {registry_.size(), false, value_name, value_name, description, join(default_value), make_repr(default_value), required};
	}
	/**
	 * @brief Registers a trigger
	 * @param argument The argument flag
	 * @param value_name The name of the argument
	 * @param description A description
	 * @param default_value The default value
	 */
	void
	register_trigger(char argument,
					 std::string value_name,
					 std::string description,
    				 bool default_value);
	/**
	 * @brief Assigns a value through the given argument flag
	 * @param result The resulting value
	 * @param argument The argument flag
	 */
	template<typename T>
	void
	assign_value(T& result,
				 char argument)
	{
		const auto row = get_argrow(argument);
		const std::string flag = make_arg_string(argument);
		result = get_value<T>(flag, row.default_value);
		bool found = false;
		for (size_t i=0; i<args_.size(); ++i) {
			if (args_[i]==flag) {
	        	if (++i<args_.size()) {
	        		result = get_value<T>(flag, args_[i]);
	        		registry_[argument].representation = make_repr(result);
					args_.erase(args_.begin()+i-1, args_.begin()+i+1);
					found = true;
					break;
	        	} else {
	                error(join("Missing value to argument '", flag, "'"));
	        	}
			}
		}
		if (row.required && !found) {
			error(join("Missing required argument '", flag, "'"));
		}
	}
	/**
	 * @brief Writes help to screen and throws an argparser_error
	 * @param message The exception message
	 */
	void
    error(const std::string& message);

private:

	struct argrow {
		argrow();
		argrow(size_t index,
			   bool is_trigger,
			   std::string value_name,
			   std::string long_value_name,
               std::string description,
			   std::string default_value,
			   std::string representation,
			   bool required);
		size_t index;
		bool is_trigger;
		std::string value_name;
		std::string long_value_name;
		std::string description;
		std::string default_value;
		std::string representation;
		bool required;
	};

    template<typename T>
    T
    get_value(std::string flag,
              std::string value)
    {
    	T result;
        try {
        	result = to_number<T>(value);
        } catch (const std::invalid_argument&) {
            error(join("The value to '", flag,"' must be numeric, not: ", value));
        }
        return result;
    }

    template<typename T>
    std::string
    make_repr(T value)
    {
    	return join(value);
    }

	std::string
	make_arg_string(char arg);

    argrow
    get_argrow(char argument);

	void
	write_help(std::ostream& stream);

	std::vector<std::string>
    expand_arguments(int argc, char **argv);

	void
	check_already_registered(char argument);

	static std::vector<std::string>
	expand_commandline_arguments(const std::vector<std::string>& arguments);

	friend std::ostream&
	operator<<(std::ostream& os, const argparser& obj);

	std::string command_line_;
    std::string app_name_;
    std::vector<std::string> args_;
    std::map<char,argrow> registry_;
    std::vector<std::pair<char,argrow>> ordered_registry_;
};
/**
 * @brief Assigns a value through the given argument flag. Spec. for bool
 * @param result The resulting value
 * @param argument The argument flag
 */
template<>
void
argparser::assign_value<bool>(bool& result,
					    	  char argument);
/**
 * @brief Returns a value for a given argument. Spec. for string
 * @param argument The argument
 * @param value The value
 * @returns The resulting value
 */
template<>
std::string
argparser::get_value<std::string>(std::string argument,
					 	 	 	  std::string value);
/**
 * @brief Returns a string repr. for a given value. Spec. for bool
 * @param value The value
 * @returns A string repr.
 */
template<>
std::string
argparser::make_repr<bool>(bool value);
/**
 * @brief Returns a string repr. for a given value. Spec. for string
 * @param value The value
 * @returns A string repr.
 */
template<>
std::string
argparser::make_repr<std::string>(std::string value);
/**
 * @brief Output stream operator for argparser
 * @param os The output stream
 * @param obj An instance of argparser
 * @returns The output stream
 */
std::ostream&
operator<<(std::ostream& os, const argparser& obj);
/**
 * @brief The exception class to indicate argument errors
 */
class argparser_error : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param message The exception message
     */
    explicit
    argparser_error(const std::string& message);
    /**
     * @brief Destructor
     */
    ~argparser_error() noexcept;
};


} // core
} // unittest
