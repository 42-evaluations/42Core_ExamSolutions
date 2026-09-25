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

// creer un alias
// a essayer pour alleger l'ecriture
// la deplacer dans la classe si tu veux la limiter juste a la classe
// using String = std::string;

class BigInt
{
private:
	typedef std::string				String;
	typedef std::string::size_type	Size;
	typedef unsigned int			UInt;

	String	_value;
	String	addStrings(const String &s1, const String &s2) const;
	void	removeZeros();

public:
	BigInt();
	BigInt(UInt n);
	BigInt(const String &num);
	BigInt(const BigInt &src);
	~BigInt();
	BigInt&			operator=(const 	BigInt &rhs);

	String			getVal() const;
	UInt			toInt(const 		String &str) const;

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
