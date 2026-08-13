#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

// std::map is used because dates ("YYYY-MM-DD") compare lexicographically in the
// same order as chronologically, so a plain ordered map gives us O(log n) exact
// lookups AND, via lower_bound(), the "closest earlier date" search the subject
// requires, with no manual scanning of the whole database.
class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void loadDatabase(const std::string& path);
		void processInputFile(const std::string& path);

	private:
		std::map<std::string, double> _db;

		bool getRate(const std::string& date, double& rate) const;

		static bool isLeapYear(int year);
		static int daysInMonth(int month, int year);
		static bool isValidDate(const std::string& date);
		static bool parseDouble(const std::string& str, double& out);
		static bool splitOnSeparator(const std::string& line, char separator,
			std::string& left, std::string& right);
		static std::string trim(const std::string& s);
};

#endif
