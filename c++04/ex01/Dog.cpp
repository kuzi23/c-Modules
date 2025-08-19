#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog()
{
	this->_type = "Dog";
	_Brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << "Dog copy constructor called" << std::endl;
	_Brain = new Brain(*other._Brain);
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog assignation operator called" << std::endl;
	if (this != &other)
    {
        Animal::operator=(other);
        delete _Brain;
        _Brain = new Brain(*other._Brain); // Copie profonde
    }
	return *this;
}

Dog::~Dog()
{
	delete _Brain;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "WOUAF WOUAF" << std::endl;
}

Brain *Dog::getBrain() const
{
	return _Brain;
}
