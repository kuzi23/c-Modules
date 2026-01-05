#include "Bureaucrat.hpp"

int main()
{
	try
	{
		std::cout << "--- Test 1: Normal Bureaucrat ---" << std::endl;
		Bureaucrat bob("Bob", 2);
		std::cout << bob << std::endl;
		bob.incrementGrade();
		std::cout << "After increment: " << bob << std::endl;
		bob.decrementGrade();
		std::cout << "After decrement: " << bob << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}
	
	std::cout << std::endl;

	try
	{
		std::cout << "--- Test 2: Grade Too High (Constructor) ---" << std::endl;
		Bureaucrat alice("Alice", 0);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		std::cout << "--- Test 3: Grade Too Low (Constructor) ---" << std::endl;
		Bureaucrat charlie("Charlie", 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		std::cout << "--- Test 4: Grade Too High (Increment) ---" << std::endl;
		Bureaucrat dave("Dave", 1);
		std::cout << dave << std::endl;
		std::cout << "Attempting to increment..." << std::endl;
		dave.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	try
	{
		std::cout << "--- Test 5: Grade Too Low (Decrement) ---" << std::endl;
		Bureaucrat eve("Eve", 150);
		std::cout << eve << std::endl;
		std::cout << "Attempting to decrement..." << std::endl;
		eve.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}
