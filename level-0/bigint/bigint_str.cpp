#include "bigint_str.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

bigint::bigint() : str("")
{
}

bigint::bigint(size_t n)
{
	std::stringstream ss;
	ss << n;
	str = ss.str();
}

bigint::bigint(std::string str) : str(str)
{
}

bigint::bigint(const bigint &other) : str(other.str)
{
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		str = other.str;
	}
	return (*this);
}

bigint::~bigint()
{
}

bigint bigint::operator+(const bigint &other) const
{
	// this      "1289496273964"
	//. other    + "32741647941"
	// add from the last digit to the left most digit
	std::string::const_reverse_iterator rit_this;
	std::string::const_reverse_iterator rit_other;
	std::string new_str;
	rit_this = this->str.rbegin();
	rit_other = other.str.rbegin();
	bool carry_on = false;
	int curr_digit_addtion = 0;

	while (*rit_this || *rit_other)
	{
		curr_digit_addtion = 0;
		if (carry_on)
			curr_digit_addtion += 1;
		if (*rit_this)
			curr_digit_addtion += *rit_this - '0';

		if (*rit_other)

			curr_digit_addtion += *rit_other - '0';

		if (curr_digit_addtion >= 10)
		{
			curr_digit_addtion = curr_digit_addtion % 10;
			std::cout << curr_digit_addtion << std::endl;
			carry_on = true;
		}
		else
			carry_on = false;
		new_str.push_back(curr_digit_addtion + '0');
		rit_this++;
		rit_other++;
	}
	// if the last addition have a last carry on
	if (carry_on)
		new_str.push_back('1');
	std::reverse(new_str.begin(), new_str.end());
	return (bigint(new_str));
}

std::string bigint::getStr() const
{
	return (this->str);
}

std::ostream &operator<<(std::ostream &os, const bigint &obj)
{
	os << obj.getStr();
	return (os);
}
