#include "bigint.hpp"
#include <cctype>

bigint::bigint(UInt n)
{
	ostringstream out;
	out << n;
	_value = out.str();
	reverse(_value.begin(), _value.end());
}

bigint::bigint(const string &num)
{
	bool valid = !num.empty();
	size_t i = 0;

	while (valid && i < num.size())
	{
		if (!isdigit(static_cast<unsigned char>(num[i])))
			valid = false;
		++i;
	}
	_value = valid ? num : "0";
	reverse(_value.begin(), _value.end());
	removeZeros();
}

string bigint::addStrings(const string &lhs, const string &rhs) const
{
	string result;
	size_t i = 0;
	size_t length = lhs.size() > rhs.size() ? lhs.size() : rhs.size();
	UInt carry = 0;

	while (i < length)
	{
		UInt left = i < lhs.size() ? lhs[i] - '0' : 0;
		UInt right = i < rhs.size() ? rhs[i] - '0' : 0;
		UInt sum = left + right + carry;
		result.push_back(static_cast<char>('0' + sum % 10));
		carry = sum / 10;
		++i;
	}
	if (carry != 0)
		result.push_back(static_cast<char>('0' + carry));
	return result;
}

void bigint::removeZeros()
{
	while (_value.size() > 1 && _value[_value.size() - 1] == '0')
		_value.erase(_value.size() - 1);
}

bigint bigint::operator+(const bigint &rhs) const
{
	bigint result;
	result._value = addStrings(_value, rhs._value);
	return result;
}

bigint &bigint::operator+=(const bigint &rhs)
{
	_value = addStrings(_value, rhs._value);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint previous(*this);
	*this += 1;
	return previous;
}

bigint &bigint::operator++()
{
	*this += 1;
	return *this;
}

bool bigint::operator>(const bigint &rhs) const
{
	if (_value.size() != rhs._value.size())
		return _value.size() > rhs._value.size();
	return _value > rhs._value;
}

bigint bigint::operator<<(const bigint &shift) const
{
	UInt count = shift.toUInt();
	bigint result(*this);

	while (count != 0)
	{
		result._value.insert(0, 1, '0'); // add 1 char '0' at indice 0 , insert(position, nombre_de_caractères, caractère)
		--count;
	}
	result.removeZeros();
	return result;
}

bigint bigint::operator>>(const bigint &shift) const
{
	UInt count = shift.toUInt();
	bigint result(*this);

	while (count != 0 && result._value.size() > 1)
	{
		result._value.erase(0, 1); // delete 1 char from indice 0
		--count;
	}
	return result;
}

bigint &bigint::operator<<=(const bigint &shift)
{
	*this = *this << shift;
	return *this;
}

bigint &bigint::operator>>=(const bigint &shift)
{
	*this = *this >> shift;
	return *this;
}
