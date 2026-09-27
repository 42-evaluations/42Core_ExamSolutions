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
		string val;

	public:
		bigint() : val("0") {}
		~bigint() {}
		bigint(UInt n);
		bigint(string num);
		bigint(const bigint &src) : val(src.val) {}
		bigint &operator=(bigint rhs)
		{
			if (this != &rhs)
				val = rhs.val;
			return *this;
		}

		string toString() const
		{
			string result(val);
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

		bool operator==(bigint rhs) const { return val == rhs.val; }
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
