#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs)
{
	(void)rhs;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

static bool isChar(std::string const &literal)
{
	return (literal.length() == 1 && !isdigit(literal[0]));
}

static bool isPseudo(std::string const &literal)
{
	return (literal == "nan" || literal == "nanf" || literal == "+inf" || literal == "+inff" || literal == "-inf" || literal == "-inff");
}

void ScalarConverter::convert(std::string const &literal)
{
	char	c = 0;
	int		i = 0;
	float	f = 0.0f;
	double	d = 0.0;
	bool	possible = true;

	// Handle Pseudo-literals
	if (isPseudo(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		
		if (literal == "nan" || literal == "nanf") {
			f = std::numeric_limits<float>::quiet_NaN();
			d = std::numeric_limits<double>::quiet_NaN();
		} else if (literal == "+inf" || literal == "+inff") {
			f = std::numeric_limits<float>::infinity();
			d = std::numeric_limits<double>::infinity();
		} else if (literal == "-inf" || literal == "-inff") {
			f = -std::numeric_limits<float>::infinity();
			d = -std::numeric_limits<double>::infinity();
		}
		std::cout << "float: " << f << "f" << std::endl;
		std::cout << "double: " << d << std::endl;
		return ;
	}

	// Handle Char Literal
	if (isChar(literal))
	{
		c = literal[0];
		i = static_cast<int>(c);
		f = static_cast<float>(c);
		d = static_cast<double>(c);
	}
	else
	{
		// Handle Numbers
		char *end;
		d = std::strtod(literal.c_str(), &end);

		// If end not empty and not 'f', or if it's 'f' (float) but there's more after it
		if ((*end != '\0' && !(*end == 'f' && *(end + 1) == '\0')))
			possible = false;
		
		if (possible)
		{
			c = static_cast<char>(d);
			i = static_cast<int>(d);
			f = static_cast<float>(d);
		}
	}

	// Output Char
	if (!possible || d < 0 || d > 127 || std::isnan(d) || std::isinf(d))
		std::cout << "char: impossible" << std::endl;
	else if (!isprint(c))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << c << "'" << std::endl;

	// Output Int
	if (!possible || d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max() || std::isnan(d) || std::isinf(d))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << i << std::endl;

	// Output Float
	if (!possible)
		std::cout << "float: impossible" << std::endl;
	else
	{
		std::cout << "float: " << f;
		if (f - static_cast<int>(f) == 0) // Add .0 if it's a whole number
			std::cout << ".0";
		std::cout << "f" << std::endl;
	}

	// Output Double
	if (!possible)
		std::cout << "double: impossible" << std::endl;
	else
	{
		std::cout << "double: " << d;
		if (d - static_cast<int>(d) == 0)
			std::cout << ".0";
		std::cout << std::endl;
	}
}
