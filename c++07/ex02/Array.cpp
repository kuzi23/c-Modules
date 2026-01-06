#include "Array.hpp"
#include "Array.tpp"
#include <iostream>

Array<T>::~Array() {
	delete [] array;
}   

