#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <deque>
#include <list>
#include <ctime>
#include <cctype>

namespace
{
	bool parsePositiveInt(const std::string& token, int& out)
	{
		if (token.empty())
			return false;
		for (size_t i = 0; i < token.size(); ++i)
			if (!std::isdigit(static_cast<unsigned char>(token[i])))
				return false;

		std::istringstream iss(token);
		long value = 0;
		iss >> value;
		if (iss.fail() || value > 2147483647L) // reject anything past INT_MAX
			return false;
		out = static_cast<int>(value);
		return true;
	}

	template <typename Container>
	void printSequence(const std::string& label, const Container& c)
	{
		std::cout << label;
		typename Container::const_iterator it = c.begin();
		for (; it != c.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: usage: ./PmergeMe <positive integers...>" << std::endl;
		return 1;
	}

	std::vector<int> input;
	for (int i = 1; i < argc; ++i)
	{
		int value;
		if (!parsePositiveInt(argv[i], value))
		{
			std::cerr << "Error: invalid argument '" << argv[i]
				<< "' (expected a positive integer)" << std::endl;
			return 1;
		}
		input.push_back(value);
	}

	printSequence("Before:", input);

	// Same input, copied into two different container types so the identical
	// PmergeMe::sort<Container> template is exercised against each of them.
	std::deque<int> deq(input.begin(), input.end());
	std::list<int> lst(input.begin(), input.end());

	PmergeMe merger;

	std::clock_t deqStart = std::clock();
	merger.sort(deq);
	std::clock_t deqEnd = std::clock();

	std::clock_t lstStart = std::clock();
	merger.sort(lst);
	std::clock_t lstEnd = std::clock();

	printSequence("After (deque):", deq);
	printSequence("After (list): ", lst);

	double deqMicroseconds =
		static_cast<double>(deqEnd - deqStart) * 1000000.0 / CLOCKS_PER_SEC;
	double lstMicroseconds =
		static_cast<double>(lstEnd - lstStart) * 1000000.0 / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << input.size()
		<< " elements with std::deque : " << deqMicroseconds << " us" << std::endl;
	std::cout << "Time to process a range of " << input.size()
		<< " elements with std::list  : " << lstMicroseconds << " us" << std::endl;

	return 0;
}
