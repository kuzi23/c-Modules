#include "Base.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(std::time(0));

	std::cout << "--- Test Loop ---" << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		Base *p = generate();
		
		std::cout << "Test " << i + 1 << ":" << std::endl;
		std::cout << "Pointer ID:   ";
		identify(p);
		
		std::cout << "Reference ID: ";
		identify(*p);
		
		std::cout << "----------------" << std::endl;
		
		delete p;
	}

	return (0);
}
