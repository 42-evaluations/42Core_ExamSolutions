/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:36:58 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/20 02:34:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

using namespace BigIntTypes;

BigInt::BigInt() : _value("0") {}

BigInt::BigInt(UInt n) {
	std::ostringstream	oss;

	oss << n;
	_value = oss.str();
	std::reverse(_value.begin(), _value.end());
}

BigInt::BigInt(const String & num) {
	bool	isNum = true;
	size_t	i = 0, len = num.size();

	while (i < len)
	{
		if (!(::isdigit(num[i])))
		{
			isNum = false;
			break ;
		}
		i++;
	}
	if (num.empty() || isNum == false)
		_value = '0';
	else
		_value = num;
	std::reverse(_value.begin(), _value.end());
	removeZeros();
}

BigInt::BigInt(const BigInt & src) {
	_value = src._value;
}

BigInt::~BigInt() {}

BigInt &	BigInt::operator=(const BigInt &rhs) {
	if (this != &rhs)
		_value = rhs._value;
	return (*this);
}

String	BigInt::addStrings(const String &s1, const String &s2) const {
	String	result;
	size_t i = 0, l1 = s1.size(), l2 = s2.size(), len;
	len = l1 > l2 ? l1 : l2;
	UInt	s1_r, // chiffre de s1
					s2_r, // chiffre de s2
					res, // resultat du calcul
					cto = 0; // carry / retenue

	while (i < len)
	{
		s1_r = i < l1 ? (s1[i] - '0') : 0;
		s2_r = i < l2 ? (s2[i] - '0') : 0;
		res = s1_r + s2_r + cto;
		cto = res / 10;
		res = res % 10;
		result.push_back(res + '0'); // convertir en char le resultat du calcul avant d'ajouter dans result
		i++;
	}
	if (cto)
		result.push_back(cto + '0');
	return (result);
}

void	BigInt::removeZeros() {
	while (_value[_value.size() - 1] == '0')
		_value.erase(_value.size() - 1);
}

String		BigInt::getVal() const {
	String ret = _value;

	std::reverse(ret.begin(), ret.end());
	return (ret);
}

UInt	BigInt::toInt(const String &str) const {
	UInt		num;
	std::istringstream	iss(str);

	iss >> num;
	return (num);
}

BigInt			BigInt::operator+(const BigInt &rhs) const {
	BigInt	result;

	result._value = addStrings(_value, rhs._value);
	return (result);
}

BigInt &		BigInt::operator+=(const BigInt &rhs) {
	_value = addStrings(_value, rhs._value);
	return (*this);
}

BigInt			BigInt::operator++(int) {
	BigInt	tmp(getVal());
	*this = *this + 1;
	return (tmp);
}

BigInt &		BigInt::operator++() {
	*this = *this + 1;
	return (*this);
}

bool			BigInt::operator==(const BigInt &rhs) const {
	return (_value == rhs._value);
}

bool			BigInt::operator!=(const BigInt &rhs) const {
	return (_value != rhs._value);
}

bool			BigInt::operator>(const BigInt &rhs) const {
	if (_value.size() != rhs._value.size())
		return (_value.size() > rhs._value.size());
	return (getVal() > rhs.getVal());
}

bool			BigInt::operator>=(const BigInt &rhs) const {
	return (!(*this < rhs));
}

bool			BigInt::operator<(const BigInt &rhs) const {
	return (!(*this > rhs) && (*this != rhs));
}

bool			BigInt::operator<=(const BigInt &rhs) const {
	return (!(*this > rhs));
}

BigInt			BigInt::operator<<(const BigInt &shift) const {
	UInt	n = toInt(shift.getVal());
	UInt	i = 0;
	BigInt	result = *this;

	while (i < n)
	{
		result._value = '0' + result._value;
		i++;
	}
	return (result);
}

BigInt			BigInt::operator>>(const BigInt &shift) const {
	UInt	n = toInt(shift.getVal());
	UInt	i = 0;
	BigInt	result = *this;

	while (i < n && !(result._value.empty()))
	{
		result._value.erase(0, 1); // delete one character from indice = 0
		i++;
	}
	return (result);
}

BigInt &		BigInt::operator<<=(const BigInt &shift) {
	_value = (*this << shift)._value;
	return (*this);
}

BigInt &		BigInt::operator>>=(const BigInt &shift) {
	_value = (*this >> shift)._value;
	return (*this);
}

std::ostream &		operator<<(std::ostream & o, const BigInt &obj) {
	o << obj.getVal() << std::endl;
	return (o);
}
