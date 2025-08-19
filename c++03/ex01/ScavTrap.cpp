#include "ScavTrap.hpp"

// ScavTrap inherits from ClapTrap
// ScavTrap has a default constructor that initializes the name attribute to "default"


ScavTrap::ScavTrap() : ClapTrap()
{
	_name = "default";
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	_guardGateMode = false;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap()
{
	_name = name;
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	_guardGateMode = false;
	std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap()
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
	*this = other;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap assignator operator called" << std::endl;
	_name = other._name;
	_hitPoints = other._hitPoints;
	_energyPoints = other._energyPoints;
	_attackDamage = other._attackDamage;
	_guardGateMode = other._guardGateMode;

	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::guardGate()
{
	_guardGateMode = !_guardGateMode;
	if (!_guardGateMode)
		std::cout << "ScavTrap " << _name << " has exited Gate keeper mode !" << std::endl;
	else
		std::cout << "ScavTrap " << _name << " has entered Gate keeper mode !" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
	if (_energyPoints == 0)
		std::cout << "ScavTrap " << _name << " has no energy points left !" << std::endl;
	else
	{
		std::cout << "ScavTrap " << _name << " headshots " << target << ", causing " << _attackDamage << " points of damage !!!!!" << std::endl;
		_energyPoints--;
	}
}
