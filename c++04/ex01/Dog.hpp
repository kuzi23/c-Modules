#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *_Brain;

	public:
		Dog();
		Dog(const Dog &other);
		Dog &operator=(const Dog &other);
		~Dog();

		void makeSound() const;
		Brain *getBrain() const;
};

#endif
