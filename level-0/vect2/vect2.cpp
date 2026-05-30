#include "vect2.hpp"

vect2::vect2()
{
	x = 0;
	y = 0;
}

vect2::vect2(int xValue, int yValue)
{
	x = xValue;
	y = yValue;
}

vect2::vect2(const vect2& other)
{
	*this = other;
}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return (*this);
}

int& vect2::operator[](int index)
{
	if (index == 0)
		return (x);
	return (y);
}

const int& vect2::operator[](int index) const
{
	if (index == 0)
		return (x);
	return (y);
}

vect2& vect2::operator+=(const vect2& other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

vect2& vect2::operator-=(const vect2& other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

vect2& vect2::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return (*this);
}

vect2 vect2::operator+(const vect2& other) const
{
	vect2 result(*this);

	result += other;
	return (result);
}

vect2 vect2::operator-(const vect2& other) const
{
	vect2 result(*this);

	result -= other;
	return (result);
}

vect2 vect2::operator*(int scalar) const
{
	vect2 result(*this);

	result *= scalar;
	return (result);
}

vect2 vect2::operator-() const
{
	return (vect2(-x, -y));
}

vect2& vect2::operator++()
{
	++x;
	++y;
	return (*this);
}

vect2 vect2::operator++(int)
{
	vect2 copy(*this);

	++(*this);
	return (copy);
}

vect2& vect2::operator--()
{
	--x;
	--y;
	return (*this);
}

vect2 vect2::operator--(int)
{
	vect2 copy(*this);

	--(*this);
	return (copy);
}

bool vect2::operator==(const vect2& other) const
{
	return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2& other) const
{
	return (!(*this == other));
}

vect2 operator*(int scalar, const vect2& vector)
{
	return (vector * scalar);
}

std::ostream& operator<<(std::ostream& out, const vect2& vector)
{
	out << "{" << vector[0] << ", " << vector[1] << "}";
	return (out);
}