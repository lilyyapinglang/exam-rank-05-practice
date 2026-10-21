#pragma once

#include <ostream>

class vect2
{
  private:
	int x;
	int y;

  public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &other);
	vect2 &operator=(const vect2 &other);
	~vect2();

	// pre increment. return *this
	vect2 &operator++();
	vect2 &operator--();
	// post increment, return oldstate
	vect2 operator++(int);
	vect2 operator--(int);

	vect2 &operator+(const vect2 &other);
	vect2 operator+(const vect2 &other) const;
	vect2 &operator-(const vect2 &other);
	vect2 &operator+=(const vect2 &other);
	vect2 &operator-=(const vect2 &other);
	vect2 &operator*=(int x);
	vect2 operator*(int x) const;
	friend vect2 operator*(int val, const vect2 &v);
	// comparison
	bool operator==(const vect2 &other) const;
	bool operator!=(const vect2 &other) const;

	// yiyuan
	vect2 operator-() const;

	//
	int &operator[](int index);
	int operator[](int index) const;

	int get_x() const;
	int get_y() const;
};

std::ostream &operator<<(std::ostream &os, const vect2 &obj);
