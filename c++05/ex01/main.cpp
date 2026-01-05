#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "--- Test 1: Bureaucrat and Form Creation ---" << std::endl;
	try {
		Bureaucrat bob("Bob", 2);
		Form formA("FormA", 2, 2);
		std::cout << bob << std::endl;
		std::cout << formA << std::endl;

		std::cout << "Signing form..." << std::endl;
		bob.signForm(formA);
		std::cout << formA << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "--- Test 2: Grade Too Low to Sign ---" << std::endl;
	try {
		Bureaucrat alice("Alice", 50);
		Form formB("FormB", 10, 10);
		std::cout << alice << std::endl;
		std::cout << formB << std::endl;

		std::cout << "Attempting to sign..." << std::endl;
		alice.signForm(formB); // Should fail
		std::cout << formB << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "--- Test 3: Invalid Form Creation ---" << std::endl;
	try {
		Form formC("FormC", 0, 10); // Too high
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	
	try {
		Form formD("FormD", 150, 151); // Too low
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return (0);
}
