#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

// The ScavTrap class inherits from the ClapTrap class
class ScavTrap : public ClapTrap
{
	private:
		bool _guardGateMode;

	public:
		ScavTrap();
		ScavTrap(const std::string& name);
		ScavTrap(const ScavTrap &other);
		ScavTrap &operator=(const ScavTrap &other);
		~ScavTrap();

		void attack(const std::string& target);
		void guardGate();
};

#endif
