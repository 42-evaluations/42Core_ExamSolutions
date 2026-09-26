/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:50:27 by pamatya           #+#    #+#             */
/*   Updated: 2025/11/20 02:05:29 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <sstream>
# include <algorithm>
# include <string>

using namespace std;

namespace BigIntTypes
{
	typedef unsigned int			UInt;
}

class BigInt
{
private:
	typedef			BigIntTypes::UInt	UInt;

	string			_value;
	string			addStrings(const string &s1, const string &s2) const;
	void			removeZeros();

public:
	BigInt();
	~BigInt();
	BigInt(UInt n);
	BigInt(const string &num);
	BigInt(const BigInt &src);
	BigInt&			operator=(const 	BigInt &rhs);

	string			getVal() const;
	UInt			toInt(const 		string &str) const;

	BigInt			operator+(const 	BigInt &rhs) const;
	BigInt&			operator+=(const 	BigInt &rhs);

	BigInt			operator++(int);
	BigInt&			operator++();

	bool			operator==(const	BigInt &rhs) const;
	bool			operator!=(const	BigInt &rhs) const;
	bool			operator>(const 	BigInt &rhs) const;
	bool			operator>=(const	BigInt &rhs) const;
	bool			operator<(const		BigInt &rhs) const;
	bool			operator<=(const	BigInt &rhs) const;

	BigInt			operator<<(const 	BigInt &shift) const;
	BigInt			operator>>(const 	BigInt &shift) const;

	BigInt&			operator<<=(const 	BigInt &shift);
	BigInt&			operator>>=(const 	BigInt &shift);
};

std::ostream&		operator<<(std::ostream &o, const BigInt &obj);

#endif
