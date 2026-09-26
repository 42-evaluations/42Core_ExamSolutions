#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <algorithm>
# include <string>

typedef unsigned int UInt;

class bigint
{
private:
	std::string addStrings(const std::string &lhs, const std::string &rhs) const;
	void removeZeros();
	std::string _value;

public:
	bigint();
	~bigint();
	bigint(UInt n);
	bigint(const std::string &num);
	bigint(const bigint &src);
	bigint &operator=(const bigint &rhs);

	std::string toString() const;
	bigint operator+(const bigint &rhs) const;
	bigint &operator+=(const bigint &rhs);
	bigint operator++(int);
	bigint &operator++();

	bool operator==(const bigint &rhs) const;
	bool operator!=(const bigint &rhs) const;
	bool operator>(const bigint &rhs) const;
	bool operator>=(const bigint &rhs) const;
	bool operator<(const bigint &rhs) const;
	bool operator<=(const bigint &rhs) const;

	bigint operator<<(const bigint &shift) const;
	bigint operator>>(const bigint &shift) const;
	bigint &operator<<=(const bigint &shift);
	bigint &operator>>=(const bigint &shift);
};

std::ostream &operator<<(std::ostream &out, const bigint &value);

#endif
