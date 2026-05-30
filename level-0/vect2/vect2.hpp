#ifndef VECT2_HPP
#define VECT2_HPP

#include "vect2.hpp"
#include <iostream>

class vect2
{
private:
	int x;
	int y;

public:
	vect2(void);
	vect2(int xValue, int yValue);
	vect2(const vect2& other);
	~vect2(void);

	vect2& operator=(const vect2& other);

	int& operator[](int index);
	const int& operator[](int index) const;

	vect2& operator+=(const vect2& other);
	vect2& operator-=(const vect2& other);
	vect2& operator*=(int scalar);

	vect2 operator+(const vect2& other) const;
	vect2 operator-(const vect2& other) const;
	vect2 operator*(int scalar) const;
	vect2 operator-(void) const;

	vect2& operator++(void);
	vect2 operator++(int);

	vect2& operator--(void);
	vect2 operator--(int);

	bool operator==(const vect2& other) const;
	bool operator!=(const vect2& other) const;
};

vect2 operator*(int scalar, const vect2& vector);
std::ostream& operator<<(std::ostream& out, const vect2& vector);

#endif