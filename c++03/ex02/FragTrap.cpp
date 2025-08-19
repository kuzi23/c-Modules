#include "FragTrap.hpp"

// FragTrap inherits from ClapTrap
// FragTrap has a default constructor that initializes the name attribute to "default"


FragTrap::FragTrap() : ClapTrap()
{
	_name = "default";
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap()
{
	_name = name;
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	std::cout << "FragTrap name constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap()
{
	std::cout << "FragTrap copy constructor called" << std::endl;
	*this = other;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	std::cout << "FragTrap assignator operator called" << std::endl;
	_name = other._name;
	_hitPoints = other._hitPoints;
	_energyPoints = other._energyPoints;
	_attackDamage = other._attackDamage;

	return *this;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::attack(const std::string& target)
{
	if (_energyPoints == 0)
		std::cout << "FragTrap " << _name << " has no energy points left !" << std::endl;
	else
	{
		std::cout << "FragTrap " << _name << " headshots " << target << ", causing " << _attackDamage << " points of damage !!!!!" << std::endl;
		_energyPoints--;
	}
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << _name << " requests a high five !" << std::endl;
	std::cout << "FragTrap " << _name << " didnt't receive a high five, aww, way to leave him hanging, friend." << std::endl;
}
