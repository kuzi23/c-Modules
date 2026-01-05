#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::srand(std::time(0)); // Seed for Robotomy

	std::cout << "--- Test 1: Shrubbery Creation ---" << std::endl;
	try {
		Bureaucrat bob("Bob", 137);
		ShrubberyCreationForm shrub("home");
		std::cout << bob << std::endl;
		std::cout << shrub << std::endl;
		bob.signForm(shrub);
		bob.executeForm(shrub);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "--- Test 2: Robotomy Request ---" << std::endl;
	try {
		Bureaucrat alice("Alice", 45);
		RobotomyRequestForm robot("Target");
		std::cout << alice << std::endl;
		std::cout << robot << std::endl;
		alice.signForm(robot);
		alice.executeForm(robot);
		alice.executeForm(robot);
		alice.executeForm(robot);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "--- Test 3: Presidential Pardon ---" << std::endl;
	try {
		Bureaucrat zaphod("Zaphod", 5);
		PresidentialPardonForm pardon("Arthur Dent");
		std::cout << zaphod << std::endl;
		std::cout << pardon << std::endl;
		zaphod.signForm(pardon);
		zaphod.executeForm(pardon);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl << "--- Test 4: Execution Rights Failure ---" << std::endl;
	try {
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon("Impossible");
		intern.signForm(pardon); // Should fail to sign
		intern.executeForm(pardon); // Should fail/not run
	} catch (std::exception &e) {
		std::cout << "Exception caught in main: " << e.what() << std::endl;
	}

	return (0);
}
