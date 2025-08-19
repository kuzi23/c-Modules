#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main()
{
    const int numAnimals = 2;
    Animal* animals[numAnimals];

    for (int i = 0; i < numAnimals / 2; ++i)
        animals[i] = new Dog();
    for (int i = numAnimals / 2; i < numAnimals; ++i)
        animals[i] = new Cat();
    for (int i = 0; i < numAnimals; ++i)
        animals[i]->makeSound();
    for (int i = 0; i < numAnimals; ++i)
        delete animals[i];

    // Verify true copies
    Dog originalDog;
    originalDog.getBrain()->setIdea(0, "Original idea");
    Dog copiedDog = originalDog;
    std::cout << "Original Dog's idea: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied Dog's idea: " << copiedDog.getBrain()->getIdea(0) << std::endl;

    return 0;
}
