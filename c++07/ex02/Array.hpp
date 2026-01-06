#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class Array
{
public:
	Array();
	Array(unsigned int n);
	Array(const Array &src);
	~Array();
	Array &operator=(const Array &src);
	T &operator[](unsigned int i);
	const T &operator[](unsigned int i) const;
	unsigned int size() const;
private:
	T *array;
	unsigned int size;
};

#endif