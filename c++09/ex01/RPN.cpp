#include "RPN.hpp"
#include <vector>
#include <sstream>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN&) {}

RPN& RPN::operator=(const RPN&)
{
	return *this;
}

RPN::~RPN() {}

RPN::RPNException::RPNException(const std::string& message) : _message(message) {}

RPN::RPNException::RPNException(const RPNException& other)
	: std::exception(other), _message(other._message) {}

RPN::RPNException& RPN::RPNException::operator=(const RPNException& other)
{
	if (this != &other)
	{
		std::exception::operator=(other);
		_message = other._message;
	}
	return *this;
}

RPN::RPNException::~RPNException() throw() {}

const char* RPN::RPNException::what() const throw()
{
	return _message.c_str();
}

bool RPN::isOperator(const std::string& token)
{
	return token.size() == 1 &&
		(token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
}

bool RPN::isPositiveInteger(const std::string& token)
{
	if (token.empty())
		return false;
	for (size_t i = 0; i < token.size(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			return false;
	return true;
}

int RPN::evaluate(const std::string& expression) const
{
	std::istringstream iss(expression);
	std::vector<int> stack;
	std::string token;

	while (iss >> token)
	{
		if (isOperator(token))
		{
			if (stack.size() < 2)
				throw RPNException("stack underflow (not enough operands)");
			int b = stack.back();
			stack.pop_back();
			int a = stack.back();
			stack.pop_back();

			int result = 0;
			switch (token[0])
			{
				case '+': result = a + b; break;
				case '-': result = a - b; break;
				case '*': result = a * b; break;
				case '/':
					if (b == 0)
						throw RPNException("division by zero");
					result = a / b;
					break;
			}
			stack.push_back(result);
		}
		else if (isPositiveInteger(token))
		{
			std::istringstream numStream(token);
			int value = 0;
			numStream >> value;
			stack.push_back(value);
		}
		else
			throw RPNException("invalid token in expression: '" + token + "'");
	}

	if (stack.size() != 1)
		throw RPNException("malformed expression (leftover operands)");
	return stack.back();
}
