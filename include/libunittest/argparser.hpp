/**
 * @brief An argument parser
 * @file argparser.hpp
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
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
	virtual
	~argparser();
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
	 * @param arg The argument flag
	 * @param value_name The name of the argument
	 * @param description A description
	 * @param default_value The default value
	 * @param display_default Whether to display the default value
	 * @param required Whether this argument is required
	 */
	template<typename T>
	void
	register_argument(char arg,
					  std::string value_name,
					  std::string description,
					  T default_value,
					  bool display_default,
					  bool required=false)
	{
		argparser::argrow row = {registry_.size(), false, value_name, value_name, description, unittest::join(default_value), this->make_repr(default_value), display_default, required};
		this->add_to_registry(arg, row);
	}
	/**
	 * @brief Registers a trigger
	 * @param arg The argument flag
	 * @param value_name The name of the argument
	 * @param description A description
	 * @param default_value The default value
	 */
	void
	register_trigger(char arg,
					 std::string value_name,
					 std::string description,
    				 bool default_value);
	/**
	 * @brief Assigns a value through the given argument flag
	 * @param result The resulting value
	 * @param arg The argument flag
	 */
	template<typename T>
	void
	assign_value(T& result,
				 char arg)
	{
		const auto row = this->from_registry(arg);
		const std::string flag = this->make_arg_string(arg);
		result = this->get_value<T>(flag, row.default_value);
		bool found = false;
		for (size_t i=0; i<args_.size(); ++i) {
			if (args_[i]==flag) {
	        	if (++i<args_.size()) {
	        		result = this->get_value<T>(flag, args_[i]);
	        		this->from_registry(arg).representation = this->make_repr(result);
					args_.erase(args_.begin()+i-1, args_.begin()+i+1);
					found = true;
					break;
	        	} else {
	        		this->error(unittest::join("Missing value to argument '", flag, "'"));
	        	}
			}
		}
		if (row.required && !found) {
			this->error(unittest::join("Missing required argument '", flag, "'"));
		}
	}
	/**
	 * @brief Returns whether the given argument flag is registered
	 * @param arg The argument flag
	 * @returns Whether the given argument flag is registered
	 */
	bool
	is_registered(char arg);
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
			   bool display_default,
			   bool required);
		size_t index;
		bool is_trigger;
		std::string value_name;
		std::string long_value_name;
		std::string description;
		std::string default_value;
		std::string representation;
		bool display_default;
		bool required;
	};

    template<typename T>
    T
    get_value(std::string flag,
              std::string value)
    {
    	T result;
        try {
        	result = unittest::core::to_number<T>(value);
        } catch (const std::invalid_argument&) {
        	this->error(unittest::join("The value to '", flag,"' must be numeric, not: ", value));
        }
        return result;
    }

    template<typename T>
    std::string
    make_repr(T value)
    {
    	return unittest::join(value);
    }

	std::string
	make_arg_string(char arg);

	void
	write_help(std::ostream& stream);

	std::vector<std::string>
    expand_arguments(int argc, char **argv);

	void
	add_to_registry(char arg, argparser::argrow row);

	bool
	in_registry(char arg);

	argparser::argrow&
	from_registry(char arg);

	friend std::ostream&
	operator<<(std::ostream& os, const argparser& obj);

	std::string command_line_;
    std::string app_name_;
    std::vector<std::string> args_;
    std::vector<std::pair<char,argparser::argrow>> registry_;
};
/**
 * @brief Assigns a value through the given argument flag. Spec. for bool
 * @param result The resulting value
 * @param arg The argument flag
 */
template<>
void
argparser::assign_value<bool>(bool& result,
					    	  char arg);
/**
 * @brief Returns a value for a given argument. Spec. for string
 * @param arg The argument
 * @param value The value
 * @returns The resulting value
 */
template<>
std::string
argparser::get_value<std::string>(std::string arg,
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
