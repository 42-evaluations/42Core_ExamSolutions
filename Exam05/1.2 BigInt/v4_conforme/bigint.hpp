#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <algorithm>
# include <string>

using namespace std;

typedef unsigned int UInt;

class bigint
{
private:
	string addStrings(const string &lhs, const string &rhs) const;
	void removeZeros();
	string _value;

public:
	bigint() : _value("0") {}
	~bigint() {}
	bigint(UInt n);
	bigint(const string &num);
	bigint(const bigint &src) : _value(src._value) {}
	bigint &operator=(const bigint &rhs)
	{
		if (this != &rhs)
			_value = rhs._value;
		return *this;
	}

	string toString() const
	{
		string result(_value);
		reverse(result.begin(), result.end());
		return result;
	}
	UInt toUInt() const
	{
		istringstream input(toString());
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

inline ostream &operator<<(ostream &out, const bigint &value)
{
	return out << value.toString();
}

#endif
