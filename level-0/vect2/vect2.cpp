#include "vect2.hpp"

vect2::vect2() : x(0), y(0)
{
}
vect2::vect2(int x, int y) : x(x), y(y)
{
}
vect2::vect2(const vect2 &other) : x(other.x), y(other.y)
{
}
vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}
vect2::~vect2()
{
}

// pre increment. return *this
vect2 &vect2::operator++()
{
	this->x++;
	this->y++;
	return (*this);
}
vect2 &vect2::operator--()
{
	this->x--;
	this->y--;
	return (*this);
}
// post increment, return oldstate
vect2 vect2::operator++(int)
{
	vect2 oldstate(*this);
	++(*this);
	return (oldstate);
}
vect2 vect2::operator--(int)
{
	vect2	oldstate;

	oldstate = *this;
	this->x--;
	this->y--;
	return (oldstate);
}

vect2 &vect2::operator+(const vect2 &other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	return (*this);
}
vect2 vect2::operator+(const vect2 &other) const
{
	vect2 a;
	a.x = this->x + other.y;
	a.y = this->y + other.y;
	return (a);
}
vect2 &vect2::operator-(const vect2 &other)
{
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	return (*this);
}
vect2 &vect2::operator+=(const vect2 &other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	return (*this);
}
vect2 &vect2::operator-=(const vect2 &other)
{
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	return (*this);
}
vect2 &vect2::operator*=(int x)
{
	this->x = this->x * x;
	this->y = this->y * x;
	return (*this);
}
vect2 vect2::operator*(int x) const
{
	vect2 a;
	a.x = this->x * x;
	a.y = this->y * x;
	return (a);
}
vect2 operator*(int val, const vect2 &v)
{
	return (v * val);
}
// comparison
bool vect2::operator==(const vect2 &other) const
{
	if (this->x == other.x && this->y == other.y)
		return (true);
	else
		return (false);
}
bool vect2::operator!=(const vect2 &other) const
{
	if (this->x == other.x && this->y == other.y)
		return (false);
	else
		return (true);
}

// yiyuan
vect2 vect2::operator-() const
{
	vect2 a;
	a.x = -this->x;
	a.y = -this->y;
	return (a);
}

//
int &vect2::operator[](int index)
{
	if (index == 0)
		return (this->x);
	if (index == 1)
		return (this->y);
	else
		throw(std::exception());
}

int vect2::operator[](int index) const
{
	const vect2 a(*this);

	if (index == 0)
		return (a.x);
	if (index == 1)
		return (a.y);
	else
		throw(std::exception());
}

int vect2::get_x() const
{
	return (this->x);
}

int vect2::get_y() const
{
	return (this->y);
}
std::ostream &operator<<(std::ostream &os, const vect2 &obj)
{
	os << obj.get_x() << ", " << obj.get_y();
	return (os);
}
