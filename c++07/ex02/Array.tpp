#pragma once

#include "Array.hpp"
#include <iostream>

template <typename T>
Array<T>::Array() : array(new T[0]), size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : array(new T[n]), size(n) {}

template <typename T>
Array<T>::Array(const Array &src) : array(new T[src.size]), size(src.size) {
	for (unsigned int i = 0; i < size; i++)
		array[i] = src.array[i];
}