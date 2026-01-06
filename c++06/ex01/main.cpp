#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data data;
	data.name = "Test Data";
	data.value = 42;

	std::cout << "Original Address: " << &data << std::endl;
	std::cout << "Original Name: " << data.name << std::endl;
	std::cout << "Original Value: " << data.value << std::endl;

	std::cout << "--------------------------------" << std::endl;

	uintptr_t raw = Serializer::serialize(&data);
	std::cout << "Serialized (uintptr_t): " << raw << std::endl;

	Data* ptr = Serializer::deserialize(raw);
	std::cout << "Deserialized Address: " << ptr << std::endl;

	std::cout << "--------------------------------" << std::endl;

	if (ptr == &data)
	{
		std::cout << "SUCCESS: Pointers match!" << std::endl;
		std::cout << "Recovered Name: " << ptr->name << std::endl;
		std::cout << "Recovered Value: " << ptr->value << std::endl;
	}
	else
	{
		std::cout << "FAILURE: Pointers do not match!" << std::endl;
	}

	return (0);
}
