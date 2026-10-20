#include "bigint_str.hpp"
#include <iostream>

int	main(void)
{
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "a + b = " << a + b << std::endl;
	// std::cout << "(c += a) = " << (c += a) << std::endl;
	std::cout << "b = " << b << std::endl;
	// std::cout << "++b = " << ++b << std::endl;
	// std::cout << "b++ = " << b++ << std::endl;
	// std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
	// std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	// std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
	std::cout << "a =" << a << std::endl;
	std::cout << "d =" << d << std::endl;
	// std::cout << "(d < a) = " << (d < a) << std::endl;
	// std::cout << "(d <= a) = " << (d <= a) << std::endl;
	// std::cout << "(d > a) = " << (d > a) << std::endl;
	// std::cout << "(d >= a) = " << (d >= a) << std::endl;
	// std::cout << "(d == a) = " << (d == a) << std::endl;
	// std::cout << "(d != a) = " << (d != a) << std::endl;
	// other
	//	// this      "1289496273964"
	//. other    + "32741647941"
	bigint x(12894962739644564546466461231564), y(32741647941);
	std::cout << "x + y = " << x + y << std::endl;
}
