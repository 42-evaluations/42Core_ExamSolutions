#include "bigint.hpp"

void removeZeros(string &val)
{
	size_t len = val.size();
	
	while (len > 1 && val[len - 1] == '0')
		val.erase(len - 1);
}

string addStrings(string lhs, string rhs)
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

bigint::bigint(UInt n)
{
	ostringstream out;
	out << n;
	val = out.str();
	reverse(val.begin(), val.end());
}

bigint::bigint(string num)
{
	bool valid = !num.empty();
	size_t i = 0;

	while (valid && i < num.size())
	{
		if (!isdigit(static_cast<unsigned char>(num[i])))
			valid = false;
		++i;
	}
	val = valid ? num : "0";
	reverse(val.begin(), val.end());
	removeZeros(val);
}

bigint bigint::operator+(bigint rhs) const
{
	bigint result;
	result.val = addStrings(val, rhs.val);
	return result;
}

bigint &bigint::operator+=(bigint rhs)
{
	val = addStrings(val, rhs.val);
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

bool bigint::operator>(bigint rhs) const
{
	if (val.size() != rhs.val.size())
		return val.size() > rhs.val.size();
	return val > rhs.val;
}

bigint bigint::operator<<(bigint shift) const
{
	UInt count = shift.toUInt();
	bigint result(*this);

	while (count != 0)
	{
		result.val.insert(0, 1, '0'); // add 1 char '0' at indice 0 , insert(position, nombre_de_caractères, caractère)
		--count;
	}
	removeZeros(result.val);
	return result;
}

bigint bigint::operator>>(bigint shift) const
{
	UInt count = shift.toUInt();
	bigint result(*this);

	while (count != 0 && result.val.size() > 1)
	{
		result.val.erase(0, 1); // delete 1 char from indice 0
		--count;
	}
	return result;
}

bigint &bigint::operator<<=(bigint shift)
{
	*this = *this << shift;
	return *this;
}

bigint &bigint::operator>>=(bigint shift)
{
	*this = *this >> shift;
	return *this;
}
