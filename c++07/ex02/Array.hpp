#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>
#include <cstdlib>

template <typename T>
class Array
{
	public:
		Array();
		Array(unsigned int n);
		Array(const Array &src);
		~Array();
		
		Array &operator=(const Array &rhs);
		T &operator[](unsigned int i);
		const T &operator[](unsigned int i) const;
		
		unsigned int size() const;

	private:
		T *_array;
		unsigned int _size;
};

#include "Array.tpp"

#endif