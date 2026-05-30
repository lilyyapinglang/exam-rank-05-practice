#ifndef BIGINTHPP
# define BIGINTHPP

# include <iostream>
# include <string>
# include <sstream>

class bigint
{
	private:
		std::string digits;

		void normalize(void);

	public:
		bigint(void);
		bigint(unsigned long num);
		bigint(const bigint& other);
		~bigint(void);

		bigint& operator=(const bigint& other);

		bigint& operator+=(const bigint& other);
		bigint operator+(const bigint& other) const;

		bigint& operator++(void);
		bigint operator++(int);

		bigint& operator<<=(unsigned int shift);
		bigint& operator<<=(const bigint& shift);
		bigint operator<<(unsigned int shift) const;
		bigint operator<<(const bigint& shift) const;

		bigint& operator>>=(unsigned int shift);
		bigint& operator>>=(const bigint& shift);
		bigint operator>>(unsigned int shift) const;
		bigint operator>>(const bigint& shift) const;

		bool operator<(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator>=(const bigint& other) const;
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;

		const std::string& getDigits(void) const;
};

std::ostream& operator<<(std::ostream& out, const bigint& num);

#endif