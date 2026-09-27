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
	bigint() : _value("0") {}
	~bigint() {}
	bigint(UInt n);
	bigint(const std::string &num);
	bigint(const bigint &src) : _value(src._value) {}
	bigint &operator=(const bigint &rhs)
	{
		if (this != &rhs)
			_value = rhs._value;
		return *this;
	}

	std::string toString() const
	{
		std::string result(_value);
		std::reverse(result.begin(), result.end());
		return result;
	}
	UInt toUInt() const
	{
		std::istringstream input(toString());
		UInt value = 0;
		input >> value;
		return value;
	}
	bigint operator+(const bigint &rhs) const;
	bigint &operator+=(const bigint &rhs);
	bigint operator++(int);
	bigint &operator++();

	bool operator==(const bigint &rhs) const { return _value == rhs._value; }
	bool operator!=(const bigint &rhs) const { return !(*this == rhs); }
	bool operator>(const bigint &rhs) const;
	bool operator>=(const bigint &rhs) const { return !(*this < rhs); }
	bool operator<(const bigint &rhs) const { return rhs > *this; }
	bool operator<=(const bigint &rhs) const { return !(*this > rhs); }

	bigint operator<<(const bigint &shift) const;
	bigint operator>>(const bigint &shift) const;
	bigint &operator<<=(const bigint &shift);
	bigint &operator>>=(const bigint &shift);
};

inline std::ostream &operator<<(std::ostream &out, const bigint &value)
{
	return out << value.toString();
}

#endif
