#include "Cat.hpp"

Cat::Cat()
{
	_Brain = new Brain();
	this->_type = "Cat";
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
	std::cout << "Cat copy constructor called" << std::endl;
	 _Brain = new Brain(*other._Brain);
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat assignation operator called" << std::endl;
	if (this != &other)
    {
        Animal::operator=(other);
        delete _Brain;
        _Brain = new Brain(*other._Brain); // Copie profonde
    }
	return *this;
}

Cat::~Cat()
{
	delete _Brain;
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Miaou" << std::endl;
}

Brain *Cat::getBrain() const
{
	return _Brain;
}
