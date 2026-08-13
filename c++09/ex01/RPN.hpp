#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <exception>

// std::vector<int> is used as a manual LIFO stack: RPN evaluation only ever needs
// push/pop/peek at the back, so a vector gives that with contiguous, cache-friendly
// storage and no adapter indirection to explain during defense.
class RPN
{
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		int evaluate(const std::string& expression) const;

		// Thrown for any malformed expression; caught in main so the program
		// always exits cleanly instead of letting an exception reach the runtime.
		class RPNException : public std::exception
		{
			public:
				explicit RPNException(const std::string& message);
				RPNException(const RPNException& other);
				RPNException& operator=(const RPNException& other);
				virtual ~RPNException() throw();

				virtual const char* what() const throw();

			private:
				std::string _message;
		};

	private:
		static bool isOperator(const std::string& token);
		static bool isPositiveInteger(const std::string& token);
};

#endif
