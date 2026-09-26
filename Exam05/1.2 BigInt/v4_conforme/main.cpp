/*
 * Previous shorter v4 test main, kept here for reference:
 *
 * #include "bigint.hpp"
 * #include <iostream>
 *
 * int main()
 * {
 *     const bigint a(42);
 *     bigint b(21), c, d(1337), e(d);
 *
 *     std::cout << "a: " << a << std::endl;
 *     std::cout << "b: " << b << std::endl;
 *     std::cout << "c: " << c << std::endl;
 *     std::cout << "d: " << d << std::endl;
 *     std::cout << "e: " << e << std::endl;
 *     std::cout << "a + b: " << a + b << std::endl;
 *     std::cout << "(c += a): " << (c += a) << std::endl;
 *     std::cout << "++b: " << ++b << std::endl;
 *     std::cout << "b++: " << b++ << std::endl;
 *     std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
 *     std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
 *     std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
 *     std::cout << "(d < a): " << (d < a) << std::endl;
 *     std::cout << "(d > a): " << (d > a) << std::endl;
 *     std::cout << "(d == a): " << (d == a) << std::endl;
 *     std::cout << "(d != a): " << (d != a) << std::endl;
 *     std::cout << "(d <= a): " << (d <= a) << std::endl;
 *     std::cout << "(d >= a): " << (d >= a) << std::endl;
 *     return 0;
 * }
 */

#include "bigint.hpp"
#include <iostream>

int main()
{
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);

	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "e: " << e << std::endl;
	std::cout << "a + b: " << a + b << std::endl;
	std::cout << "(c += a): " << (c += a) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "++b: " << ++b << std::endl;
	std::cout << "b++: " << b++ << std::endl;
	std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d < a): " << (d < a) << std::endl;
	std::cout << "(d > a): " << (d > a) << std::endl;
	std::cout << "(d == a): " << (d == a) << std::endl;
	std::cout << "(d != a): " << (d != a) << std::endl;
	std::cout << "(d <= a): " << (d <= a) << std::endl;
	std::cout << "(d >= a): " << (d >= a) << std::endl;
	std::cout << std::endl;
	d = e;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "(e <= d): " << (e <= d) << std::endl;
	std::cout << "(e >= d): " << (e >= d) << std::endl;
	std::cout << "(e < d): " << (e < d) << std::endl;
	std::cout << "(e > d): " << (e > d) << std::endl;

	std::cout << std::endl;
	bigint	f((d + 1));
	bigint	g(d);
	bigint	h(d + f);
	bigint	i(1234);
	bigint	j(i + 1);
	std::cout << "d = " << d << "f(d + 1) = " << f << "g(d) + 1 = " << (g + 1) << "h(d + f) = " << h << "i(1234) = " << i << "j(i + 1) = " << j << std::endl;
	std::cout << "(f > d): " << (f > d) << std::endl;
	std::cout << "(f < d): " << (f < d) << std::endl;
	std::cout << "f >= d: " << (f >= d) << std::endl;
	std::cout << "f <= d: " << (f <= d) << std::endl;

	return (0);
}
