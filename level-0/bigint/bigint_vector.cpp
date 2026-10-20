#include "bigint.hpp"
#include <cstdlib>
#include <deque>
#include <iterator>
#include <string>

bigint::bigint() : str({})
{
}

bigint::bigint(std::deque<char> str) : str(str)
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
	std::deque<char> result;
	std::string::reverse_iterator rit_this;
	std::string::reverse_iterator rit_other;
	if (this->str.size() > other.str.size())
	{
		// other fill 0 in front,
	}
	else if (this->str.size() < other.str.size())
	{ // this fill 0 front;
	}
	bool carry_on = false;
	for (rit_this = this->str.rbegin(); rit_this != this->str.rend(); ++rit_this)
	{
		for (rit_other = other.str.rbegin(); rit_other != other.str.rend(); ++rit_other)
		{
			int curr_digit_addtion = (int)(*rit_other) + (int)(*rit_this)
				+ carry_on;
			if (curr_digit_addtion > 10)
			{
				carry_on = true;
				curr_digit_addtion = curr_digit_addtion - 10;
			}
			else
				result.push_front(curr_digit_addtion);
		}
	}
	return (bigint(result));
}
