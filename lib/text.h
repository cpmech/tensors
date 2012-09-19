/*************************************************************************************
 * Tensors - A C++ library to work with tensors                                      *
 * Copyright (C) 2004 Dorival de Moraes Pedroso <dorival.pedroso em gmail.com>       *
 *                                                                                   *
 * This file is part of Tensors.                                                     *
 *                                                                                   *
 * Tensors is free software; you can redistribute it and/or modify it under the      *
 * terms of the GNU General Public License as published by the Free Software         *
 * Foundation; either version 2 of the License, or (at your option) any later        *
 * version.                                                                          *
 *                                                                                   *
 * Tensors is distributed in the hope that it will be useful, but WITHOUT ANY        *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A   *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.          *
 *                                                                                   *
 * You should have received a copy of the GNU General Public License along with      *
 * Tensors; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, *
 * Fifth Floor, Boston, MA 02110-1301, USA                                           *
 *************************************************************************************/


// PS.: This class is very dirty....

#include <iostream>
#include <string>
#include <sstream>
#include <complex>

class Text
{
public:
	// Constructor
	Text(){}
	// Alternative Constructor
	Text(const char Rgt[])
	{
		if (Rgt) _text.assign(Rgt);
	}
	Text(const int & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	Text(const long & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	Text(const double & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	Text(const std::complex<double> & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	// Copy constructor
	Text (const Text & Rgt)
	{
		_text = Rgt._text;
	}
	// Methods
	std::string       * GetString()       { return (&_text); }
	std::string const * GetString() const { return (&_text); }
	// Assing operators
	void operator= (const Text & Rgt)
	{
		_text = Rgt._text;
	}
	void operator= (const char Rgt[])
	{
		if (Rgt) _text.assign(Rgt);
	}
	void operator= (const int & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	void operator= (const long & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	void operator= (const double & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	void operator= (const std::complex<double> & Rgt)
	{
		std::ostringstream oss;
		oss << Rgt;
		_text = oss.str();
	}
	void operator= (const std::string & Rgt)
	{
		_text = Rgt;
	}
	// Binary operators
	Text operator+ (const Text & Rgt) const
	{
		Text res;
		if      (_text=="0")
			res = Rgt._text;
		else if (Rgt._text=="0")
			res = _text;
		else if (("-"+_text)==Rgt._text)
			res = "0";
		else if (("-"+Rgt._text)==_text)
			res = "0";
		// 1/2
		else if (_text=="1/2" & Rgt._text=="1/2")
			res = "1";
		else if (_text=="1" & Rgt._text=="1/2")
			res = "3/2";
		else if (_text=="1" & Rgt._text=="-1/2")
			res = "1/2";
		else if (_text=="3/2" & Rgt._text=="1/2")
			res = "2";
		// -1/3, 1/6 and others
		else if (_text=="-1/3" & Rgt._text=="1/2")
			res = "1/6";
		else if (_text=="1/6" & Rgt._text=="1/2")
			res = "2/3";
		// sqrt(2)
		else if (_text=="1/sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "sqrt(2)";
		else if (_text=="2*sqrt(2)" & Rgt._text=="3*sqrt(2)")
			res = "5*sqrt(2)";
		else if (_text=="-2*sqrt(2)" & Rgt._text=="3*sqrt(2)")
			res = "sqrt(2)";
		else if (_text=="2*sqrt(2)" & Rgt._text=="-3*sqrt(2)")
			res = "-sqrt(2)";
		else if (_text=="3*sqrt(2)" & Rgt._text=="2*sqrt(2)")
			res = "5*sqrt(2)";
		else if (_text=="3*sqrt(2)" & Rgt._text=="-2*sqrt(2)")
			res = "sqrt(2)";
		else if (_text=="-3*sqrt(2)" & Rgt._text=="2*sqrt(2)")
			res = "-sqrt(2)";
		// others
		else if (_text==Rgt._text)
		{
			if (_text=="sqrt(2)/4")
				res = "1/sqrt(2)";
			else if (_text=="-sqrt(2)/4")
				res = "-1/sqrt(2)";
			else
			{
				std::string * ptr;
				ptr = res.GetString();
				ptr->append("2*");
				ptr->append(_text);
			}
		}
		else
			res = _text + "+" + Rgt._text;
		return res;
	}
	Text operator- (const Text & Rgt) const
	{
		Text res;
		if      (Rgt._text=="0")
			res = _text;
		else if (_text=="0")
		{
			std::string * ptr;
			ptr = res.GetString();
			ptr->append("-");
			ptr->append(Rgt._text);
		}
		else if (_text==Rgt._text)
			res = "0";
		else
			res = _text + "-" + Rgt._text;
		return res;
	}
	Text operator* (const Text & Rgt) const
	{
		Text res;
		if      (_text=="0" | Rgt._text=="0")
			res = "0";
		else if (_text=="1")
			res = Rgt._text;
		else if (Rgt._text=="1")
			res = _text;
		// 1/2
		else if (_text=="2" & Rgt._text=="1/2")
			res = "1";
		else if (_text=="1/2" & Rgt._text=="2")
			res = "1";
		// 1/3
		else if (_text=="3" & Rgt._text=="1/3")
			res = "1";
		else if (_text=="1/3" & Rgt._text=="3")
			res = "1";
		// sqrt(2)
		else if (_text=="sqrt(2)" & Rgt._text=="sqrt(2)")
			res = "2";
		else if (_text=="1/sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "1/2";
		else if (_text=="1/sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-1/2";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "-1/2";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "1/2";

		else if (_text=="2" & Rgt._text=="-1/sqrt(2)")
			res = "-2/sqrt(2)";
		else if (_text=="sqrt(2)/4" & Rgt._text=="1/sqrt(2)")
			res = "1/4";
		else if (_text=="-sqrt(2)/4" & Rgt._text=="1/sqrt(2)")
			res = "-1/4";
		else if (_text=="2*sqrt(2)/4" & Rgt._text=="-1/sqrt(2)")
			res = "-1/2";
		else if (_text=="2*sqrt(2)/4" & Rgt._text=="1/sqrt(2)")
			res = "1/2";

		else if (_text=="2" & Rgt._text=="sqrt(2)/4")
			res = "1/sqrt(2)";
		else if (_text=="2" & Rgt._text=="-sqrt(2)/4")
			res = "-1/sqrt(2)";
		else if (_text=="-2" & Rgt._text=="sqrt(2)/4")
			res = "-1/sqrt(2)";
		else if (_text=="1/2" & Rgt._text=="1/sqrt(2)")
			res = "sqrt(2)/4";
		else if (_text=="-1/2" & Rgt._text=="1/sqrt(2)")
			res = "-sqrt(2)/4";
		else if (_text=="1/2" & Rgt._text=="-1/sqrt(2)")
			res = "-sqrt(2)/4";
		else if (_text=="-1/2" & Rgt._text=="-1/sqrt(2)")
			res = "sqrt(2)/4";
		else if (_text=="1/sqrt(2)" & Rgt._text=="1/2")
			res = "sqrt(2)/4";
		else if (_text=="1/sqrt(2)" & Rgt._text=="-1/2")
			res = "-sqrt(2)/4";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="1/2")
			res = "-sqrt(2)/4";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="-1/2")
			res = "sqrt(2)/4";

		else if (_text=="2" & Rgt._text=="1/sqrt(2)")
			res = "sqrt(2)";
		else if (_text=="4" & Rgt._text=="1/sqrt(2)")
			res = "2*sqrt(2)";
		else if (_text=="1/sqrt(2)" & Rgt._text=="4")
			res = "2*sqrt(2)";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="4")
			res = "-2*sqrt(2)";
		else if (_text=="6" & Rgt._text=="1/sqrt(2)")
			res = "3*sqrt(2)";
		else if (_text=="1/sqrt(2)" & Rgt._text=="6")
			res = "3*sqrt(2)";

		else if (_text=="sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "1";
		else if (_text=="2*sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "2";
		else if (_text=="3*sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "3";
		else if (_text=="4*sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "4";
		else if (_text=="5*sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "5";
		else if (_text=="6*sqrt(2)" & Rgt._text=="1/sqrt(2)")
			res = "6";
		
		else if (_text=="1/sqrt(2)" & Rgt._text=="sqrt(2)")
			res = "1";
		else if (_text=="1/sqrt(2)" & Rgt._text=="2*sqrt(2)")
			res = "2";
		else if (_text=="1/sqrt(2)" & Rgt._text=="3*sqrt(2)")
			res = "3";
		else if (_text=="1/sqrt(2)" & Rgt._text=="4*sqrt(2)")
			res = "4";
		else if (_text=="1/sqrt(2)" & Rgt._text=="5*sqrt(2)")
			res = "5";
		else if (_text=="1/sqrt(2)" & Rgt._text=="6*sqrt(2)")
			res = "6";

		else if (_text=="sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-1";
		else if (_text=="2*sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-2";
		else if (_text=="3*sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-3";
		else if (_text=="4*sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-4";
		else if (_text=="5*sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-5";
		else if (_text=="6*sqrt(2)" & Rgt._text=="-1/sqrt(2)")
			res = "-6";

		else if (_text=="-1/sqrt(2)" & Rgt._text=="sqrt(2)")
			res = "-1";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="2*sqrt(2)")
			res = "-2";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="3*sqrt(2)")
			res = "-3";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="4*sqrt(2)")
			res = "-4";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="5*sqrt(2)")
			res = "-5";
		else if (_text=="-1/sqrt(2)" & Rgt._text=="6*sqrt(2)")
			res = "-6";

		// sqrt(3)
		else if (_text=="sqrt(3)" & Rgt._text=="sqrt(3)")
			res = "3";
		else if (_text=="1/sqrt(3)" & Rgt._text=="1/sqrt(3)")
			res = "1/3";
		else if (_text=="-1/sqrt(3)" & Rgt._text=="1/sqrt(3)")
			res = "-1/3";
		else if (_text=="1/sqrt(3)" & Rgt._text=="-1/sqrt(3)")
			res = "-1/3";
		else if (_text=="-1/sqrt(3)" & Rgt._text=="-1/sqrt(3)")
			res = "1/3";
		else if (_text=="3" & Rgt._text=="1/sqrt(3)")
			res = "sqrt(3)";
		// others
		else if (_text=="2" & Rgt._text=="2")
			res = "4";
		else
			res = _text + "*" + Rgt._text;
		return res;
	}
	Text operator/ (const Text & Rgt) const
	{
		Text res;
		if      (Rgt._text=="0")
			res = "NaN";
		else if (_text=="0")
			res = "0";
		else if (_text==Rgt._text)
			res = "1";
		else if (_text=="2" & Rgt._text=="sqrt(2)")
			res = "sqrt(2)";
		else if (_text=="3" & Rgt._text=="sqrt(3)")
			res = "sqrt(3)";
		else
			res = _text + "/" + Rgt._text;
		return res;
	}
private:
	std::string _text;
};

std::ostream & operator<< (std::ostream & output, const Text & tex)
{
	std::string const * ptr;
	ptr = tex.GetString();
	output << (*ptr);
	return output;
}

std::istream & operator>> (std::istream & input, Text & tex)
{
	std::string * ptr;
	ptr = tex.GetString();
	input >> (*ptr);
	return input;
}

Text sqrt (const Text & tex)
{
	Text res;
	std::string const * ptr;
	ptr = tex.GetString();
	res = "sqrt(" + (*ptr) + ")";
	return res;
}
