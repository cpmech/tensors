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

#ifndef TENSORS_TENSOR1_H
#define TENSORS_TENSOR1_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cmath>

#define DEFAULT_WID 4

namespace TensorsLib
{

template<typename Type, int Dim>
class Tensor1
{
public:
	// Constructor
	Tensor1();

	// Alternative Constructor
	Tensor1 (const Type & Val);
	Tensor1 (const std::string & strVals);

	// Copy Constructor
	Tensor1 (const Tensor1<Type,Dim> & Rgt);

	// Methods
	void SetPrintCol  (bool PrintCol) { _print_col = PrintCol; }
	bool GetPrintCol  () const        { return _print_col; }
	void SetWid       (int CellWidth) { _cell_wid = CellWidth; }
	int  GetWid       () const        { return _cell_wid; }
	void Clear        ();
	Type GetEuclidNorm() const;
	Type Norm         () const { return GetEuclidNorm(); }
	void SetMaxima    (bool Maxima=true) { _maxima = Maxima; }
	bool Maxima       () const           { return _maxima; }

	// Operator Overloading
	void         operator=  (const Tensor1<Type,Dim> & Rgt);
	Type       & operator[] (int i);
	const Type & operator[] (int i) const;

	// Binary operators
	Tensor1<Type,Dim> operator+ (const Tensor1<Type,Dim> & Rgt) const;
	Tensor1<Type,Dim> operator- (const Tensor1<Type,Dim> & Rgt) const;
	Tensor1<Type,Dim> operator* (const Type & Rgt)              const;
	Tensor1<Type,Dim> operator/ (const Type & Rgt)              const;

	// Assign values separated by commas
	class CommaAssign
	{
	public:
		CommaAssign(Type * Values, Type const & FirstValue) : _values(Values), _i(0)
		{
			_values[_i] = FirstValue;
		}
		CommaAssign & operator, (Type const & Num) 
		{
            _i++;
			_values[_i] = Num;
			return *this;
		}
	private:
		Type * _values;
		int    _i;
	};
	CommaAssign operator= (Type const & Num) { return CommaAssign(_components, Num); }

protected:
	int  _cell_wid;
	bool _print_col;
	Type _components[Dim];

private:
	bool _maxima;
};

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor1<Type, Dim> & T1);

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor1<Type, Dim> & T1);


/////////////////////////////////////////////////////////////////////////////////


// Constructor
template<typename Type, int Dim>
Tensor1<Type,Dim>::Tensor1() : _cell_wid(DEFAULT_WID), _print_col(false), _maxima(false)
{
	for (int i=0; i<Dim; ++i)
		_components[i] = static_cast<Type>(0);
}

// Alternative Constructor
template<typename Type, int Dim>
Tensor1<Type,Dim>::Tensor1 (const Type & Val) : _cell_wid(DEFAULT_WID), _print_col(false), _maxima(false)
{
	for (int i=0; i<Dim; ++i) 
		_components[i] = Val;
}
template<typename Type, int Dim>
Tensor1<Type,Dim>::Tensor1 (const std::string & strVals) : _cell_wid(DEFAULT_WID), _print_col(false), _maxima(false)
{
	std::istringstream iss(strVals);
	iss >> (*this);
}

// Copy Constructor
template<typename Type, int Dim>
Tensor1<Type,Dim>::Tensor1 (const Tensor1<Type,Dim> & Rgt) : _cell_wid(DEFAULT_WID), _print_col(false), _maxima(false)
{
	for (int i=0; i<Dim; ++i)
		_components[i] = Rgt._components[i];
}

// Methods
template<typename Type, int Dim>
void Tensor1<Type,Dim>::Clear()
{
	for (int i=0; i<Dim; ++i)
		_components[i] = static_cast<Type>(0);
}

template<typename Type, int Dim>
Type Tensor1<Type,Dim>::GetEuclidNorm() const
{
	Type sum = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i) 
		sum = sum + _components[i] * _components[i];
	return static_cast<Type>(sqrt(sum));
}

// Operator Overloading
template<typename Type, int Dim>
void Tensor1<Type,Dim>::operator= (const Tensor1<Type,Dim> & Rgt)
{
	assert (&Rgt!=this);
	for (int i=0; i<Dim; ++i) 
		_components[i] = Rgt._components[i];
}

template<typename Type, int Dim>
Type & Tensor1<Type,Dim>::operator[] (int i)
{
	assert(i>=0 && i<Dim);
	return _components[i];
}

template<typename Type, int Dim>
const Type & Tensor1<Type,Dim>::operator[] (int i) const
{
	assert(i>=0 && i<Dim);
	return _components[i];
}

// Binary operators
template<typename Type, int Dim>
Tensor1<Type,Dim> Tensor1<Type,Dim>::operator+ (const Tensor1<Type,Dim> & Rgt) const
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _components[i] + Rgt._components[i];
	return res;
}

template<typename Type, int Dim>
Tensor1<Type,Dim> Tensor1<Type,Dim>::operator- (const Tensor1<Type,Dim> & Rgt) const
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _components[i] - Rgt._components[i];
	return res;
}

template<typename Type, int Dim>
Tensor1<Type,Dim> Tensor1<Type,Dim>::operator* (const Type & Rgt) const
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _components[i] * Rgt;
	return res;
}

template<typename Type, int Dim>
Tensor1<Type,Dim> Tensor1<Type,Dim>::operator/ (const Type & Rgt) const
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _components[i] / Rgt;
	return res;
}

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor1<Type, Dim> & T1)
{
	for (int i=0; i<Dim; ++i)
		input >> T1[i];
	return input;
}

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor1<Type, Dim> & T1)
{
    if (T1.Maxima())
    {
        output << "matrix(";
        for (int i=0; i<Dim; ++i)
        {
            output << "[" << T1[i] << "]";
            if (i!=Dim-1) output << ",";
        }
        output << "), ratsimp;" << std::endl;
    }
    else
    {
        for (int i=0; i<Dim; ++i)
        {
            if (T1.GetPrintCol())
                output << std::setw(T1.GetWid()) << T1[i] << std::endl;
            else
                output << std::setw(T1.GetWid()) << T1[i] << " ";
        }
    }
	return output;
}

}; // namespace TensorsLib

#endif
