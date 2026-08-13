#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, end - start + 1);
}

bool BitcoinExchange::splitOnSeparator(const std::string& line, char separator,
	std::string& left, std::string& right)
{
	size_t pos = line.find(separator);
	if (pos == std::string::npos)
		return false;
	left = trim(line.substr(0, pos));
	right = trim(line.substr(pos + 1));
	return (!left.empty() && !right.empty());
}

bool BitcoinExchange::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::daysInMonth(int month, int year)
{
	static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && isLeapYear(year))
		return 29;
	return days[month - 1];
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	// Expected strict format: YYYY-MM-DD (10 chars, dashes at positions 4 and 7).
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	std::istringstream yearStream(date.substr(0, 4));
	std::istringstream monthStream(date.substr(5, 2));
	std::istringstream dayStream(date.substr(8, 2));
	int year = 0, month = 0, day = 0;
	yearStream >> year;
	monthStream >> month;
	dayStream >> day;

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > daysInMonth(month, year))
		return false;
	return true;
}

bool BitcoinExchange::parseDouble(const std::string& str, double& out)
{
	if (str.empty())
		return false;
	std::istringstream iss(str);
	iss >> out;
	if (iss.fail())
		return false;
	std::string leftover;
	if (iss >> leftover) // anything left after the number means trailing garbage
		return false;
	return true;
}

void BitcoinExchange::loadDatabase(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file: " << path << std::endl;
		return; // keep going with an empty database rather than crash the program
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(file, line))
	{
		if (firstLine)
		{
			firstLine = false;
			if (line == "date,exchange_rate")
				continue; // skip the CSV header row
		}
		if (trim(line).empty())
			continue;

		std::string date, valueStr;
		if (!splitOnSeparator(line, ',', date, valueStr))
			continue; // malformed database row: skip rather than abort loading
		if (!isValidDate(date))
			continue;
		double rate;
		if (!parseDouble(valueStr, rate))
			continue;
		_db[date] = rate;
	}
}

bool BitcoinExchange::getRate(const std::string& date, double& rate) const
{
	std::map<std::string, double>::const_iterator it = _db.lower_bound(date);
	if (it != _db.end() && it->first == date)
	{
		rate = it->second;
		return true;
	}
	if (it == _db.begin())
		return false; // requested date is earlier than every entry in the database
	--it; // step back to the closest earlier date
	rate = it->second;
	return true;
}

void BitcoinExchange::processInputFile(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool firstLine = true;
	while (std::getline(file, line))
	{
		if (firstLine)
		{
			firstLine = false;
			if (trim(line) == "date | value")
				continue; // skip the expected header row
		}
		if (trim(line).empty())
			continue;

		std::string date, valueStr;
		if (!splitOnSeparator(line, '|', date, valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		double value;
		if (!parseDouble(valueStr, value))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		double rate;
		if (!getRate(date, rate))
		{
			std::cerr << "Error: no earlier database entry for date => " << date << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
	}
}
