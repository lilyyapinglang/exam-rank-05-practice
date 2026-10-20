#ifndef BIGINT_HPP
# define BIGINT_HPP

/*
Create a class called bigint that will store an arbitrary precision unsigned
integer.
*/
class bigint
{
	// storing an array or a
	// string containing the different "parts" of the number??
  private:
	unsigned int size;
	std::string str;

  public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint &other);
	bigint &operator=(const bigint &other);
	~bigint();

	// addition
	bigint &operator+(const bigint &other) const;
	bigint &operator+=(const bigint &other) const;
	// increment
	// post increment takes an int argument, why ???
	bigint operator++(int);
	bigint operator--(int);
	// pre increment takes no argement, i fotgot why ...
	bigint &operator++();
	bigint &operator--();

	// comparison operators
	bool operator==(const bigint &other) const;
	bool operator!=(const bigint &other) const;
	bool operator>(const bigint &other) const;
	bool operator>=(const bigint &other) const;
	bool operator<(const bigint &other) const;
	bool operator<=(const bigint &other) const;
	// digit shift operators
	// 42 << 3 == 42000, * 10^3
	bigint &operator<<(unsigned int digits2shift); // ?
	bigint &operator<<=(unsigned int digits2shift);
	// 1337 >> 2 == 13, /10^2
	bigint &operator>>(unsigned int digits2shift);
	bigint &operator>>=(unsigned int digits2shift);
};

std::ostream &operator<<(std::ostream &os, const bigint &obj);
#endif