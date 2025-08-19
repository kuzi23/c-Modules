#include "ClapTrap.hpp"


ClapTrap::ClapTrap() : _name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap " << name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = other;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
	std::cout << "ClapTrap assignator operator called" << std::endl;
	_name = other._name;
	_hitPoints = other._hitPoints;
	_energyPoints = other._energyPoints;
	_attackDamage = other._attackDamage;

	return *this;
}

void ClapTrap::attack(const std::string& target) {
	if (_energyPoints == 0) {
		std::cout << "ClapTrap " << _name << " has no energy points left !" << std::endl;
	}
	else {
		std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage !" << std::endl;
		_energyPoints--;
	}
}

void ClapTrap::takeDamage(unsigned int amount) {
	_hitPoints -= amount;
	if (_hitPoints <= 0) {
		_hitPoints = 0;
		std::cout << "ClapTrap " << _name << " has died, press F to pay respects" << std::endl;
	}
	else {
		std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage !" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (_energyPoints == 0) {
		std::cout << "ClapTrap " << _name << " has no energy points left !" << std::endl;
	}
	else {
		std::cout << "ClapTrap " << _name << " repairs itself for " << amount << " points of health !" << std::endl;
		_energyPoints--;
		_hitPoints += amount;
	}
}
