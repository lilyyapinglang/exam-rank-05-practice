#include "bigint.hpp"

bigint::bigint() : digits("0") {}

bigint::bigint(unsigned long num)
{
	std::stringstream ss;

	ss << num;
	digits = ss.str();
}

bigint::bigint(const bigint& other)
{
	*this = other;
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		digits = other.digits;
	return (*this);
}

static unsigned int stringToUINT(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;

	res = 0;
	ss >> res;
	return (res);
}

void bigint::normalize()
{
	std::size_t pos;

	pos = digits.find_first_not_of('0');
	if (pos == std::string::npos)
		digits = "0";
	else if (pos > 0)
		digits.erase(0, pos);
}

const std::string& bigint::getDigits() const
{
	return (digits);
}

bigint& bigint::operator+=(const bigint& other)
{
	std::string result;
	int carry;
	int sum;
	int leftNum;
	int rightNum;
	int i;
	int j;

	result = "";
	carry = 0;
	i = static_cast<int>(digits.size()) - 1;
	j = static_cast<int>(other.digits.size()) - 1;
	while (i >= 0 || j >= 0 || carry != 0)
	{
		leftNum = 0;
		rightNum = 0;
		if (i >= 0)
			leftNum = digits[i--] - '0';
		if (j >= 0)
			rightNum = other.digits[j--] - '0';
		sum = leftNum + rightNum + carry;
		result.insert(result.begin(), static_cast<char>('0' + (sum % 10)));
		carry = sum / 10;
	}
	digits = result;
	normalize();
	return (*this);
}

bigint bigint::operator+(const bigint& other) const
{
	bigint result(*this);

	result += other;
	return (result);
}

bigint& bigint::operator++()
{
	*this += 1;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint copy(*this);

	++(*this);
	return (copy);
}

bigint& bigint::operator<<=(unsigned int shift)
{
	if (digits != "0")
		digits.append(shift, '0');
	return (*this);
}

bigint& bigint::operator<<=(const bigint& shift)
{
	*this <<= stringToUINT(shift.digits);
	return (*this);
}

bigint bigint::operator<<(unsigned int shift) const
{
	bigint result(*this);

	result <<= shift;
	return (result);
}

bigint bigint::operator<<(const bigint& shift) const
{
	bigint result(*this);

	result <<= shift;
	return (result);
}

bigint& bigint::operator>>=(unsigned int shift)
{
	if (shift >= digits.size())
		digits = "0";
	else
		digits.erase(digits.size() - shift);
	return (*this);
}

bigint& bigint::operator>>=(const bigint& shift)
{
	*this >>= stringToUINT(shift.digits);
	return (*this);
}

bigint bigint::operator>>(unsigned int shift) const
{
	bigint result(*this);

	result >>= shift;
	return (result);
}

bigint bigint::operator>>(const bigint& shift) const
{
	bigint result(*this);

	result >>= shift;
	return (result);
}

bool bigint::operator<(const bigint& other) const
{
	if (digits.size() != other.digits.size())
		return (digits.size() < other.digits.size());
	return (digits < other.digits);
}

bool bigint::operator<=(const bigint& other) const
{
	return (!(*this > other));
}

bool bigint::operator>(const bigint& other) const
{
	return (other < *this);
}

bool bigint::operator>=(const bigint& other) const
{
	return (!(*this < other));
}

bool bigint::operator==(const bigint& other) const
{
	return (digits == other.digits);
}

bool bigint::operator!=(const bigint& other) const
{
	return (!(*this == other));
}

std::ostream& operator<<(std::ostream& out, const bigint& num)
{
	out << num.getDigits();
	return (out);
}