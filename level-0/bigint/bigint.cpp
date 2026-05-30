#include "bigint.hpp"

bigint::bigint(void) : digits("0")
{
}

bigint::bigint(unsigned long num)
{
	if (num == 0)
	{
		digits = "0";
		return;
	}
	while (num > 0)
	{
		digits.insert(digits.begin(), static_cast<char>('0' + (num % 10)));
		num /= 10;
	}
}

bigint::bigint(const bigint& other)
{
	*this = other;
}

bigint::~bigint(void)
{
}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		digits = other.digits;
	return (*this);
}

void bigint::normalize(void)
{
	std::size_t pos;

	pos = digits.find_first_not_of('0');
	if (pos == std::string::npos)
		digits = "0";
	else if (pos > 0)
		digits.erase(0, pos);
}

std::size_t bigint::toSizeLimit(std::size_t limit) const
{
	std::size_t result;
	std::size_t i;

	result = 0;
	i = 0;
	while (i < digits.size())
	{
		if (result > limit / 10)
			return (limit + 1);
		result = result * 10 + (digits[i] - '0');
		if (result > limit)
			return (limit + 1);
		i++;
	}
	return (result);
}

const std::string& bigint::getDigits(void) const
{
	return (digits);
}

bigint& bigint::operator+=(const bigint& other)
{
	std::string result;
	int carry;
	int sum;
	int a;
	int b;
	int i;
	int j;

	result = "";
	carry = 0;
	i = static_cast<int>(digits.size()) - 1;
	j = static_cast<int>(other.digits.size()) - 1;
	while (i >= 0 || j >= 0 || carry != 0)
	{
		a = 0;
		b = 0;
		if (i >= 0)
			a = digits[i--] - '0';
		if (j >= 0)
			b = other.digits[j--] - '0';
		sum = a + b + carry;
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

bigint& bigint::operator++(void)
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

bigint bigint::operator<<(unsigned int shift) const
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
	std::size_t amount;

	amount = shift.toSizeLimit(digits.size());
	if (amount >= digits.size())
		digits = "0";
	else
		digits.erase(digits.size() - amount);
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