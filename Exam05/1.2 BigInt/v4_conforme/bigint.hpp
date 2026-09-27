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
	string addStrings(string lhs, string rhs) const;
	void removeZeros();
	string _value;

public:
	bigint() : _value("0") {}
	~bigint() {}
	bigint(UInt n);
	bigint(string num);
	bigint(const bigint &src) : _value(src._value) {}
	bigint &operator=(bigint rhs)
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
	bigint operator+(bigint rhs) const;
	bigint &operator+=(bigint rhs);
	bigint operator++(int);
	bigint &operator++();

	bool operator==(bigint rhs) const { return _value == rhs._value; }
	bool operator!=(bigint rhs) const { return !(*this == rhs); }
	bool operator>(bigint rhs) const;
	bool operator>=(bigint rhs) const { return !(*this < rhs); }
	bool operator<(bigint rhs) const { return rhs > *this; }
	bool operator<=(bigint rhs) const { return !(*this > rhs); }

	bigint operator<<(bigint shift) const;
	bigint operator>>(bigint shift) const;
	bigint &operator<<=(bigint shift);
	bigint &operator>>=(bigint shift);
};

inline ostream &operator<<(ostream &out, const bigint &value)
{
	return out << value.toString();
}

#endif
