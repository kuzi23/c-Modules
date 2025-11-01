
#pragma once

// includes
#include <string>
#include <iostream>

// classes
class Zombie
{
	private:
		std::string	_name;
	public:
	// Constructors
		Zombie(std::string s);
	// Deconstructors
		~Zombie();
	// Public Methods
		void	announce(void)const;

};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);
