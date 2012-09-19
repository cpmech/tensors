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

#ifndef TENSORS_TENSOR3_H
#define TENSORS_TENSOR3_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "tensor2.h"

namespace TensorsLib
{

template<typename Type, int Dim>
class Tensor3
{
public:
	// Constructor
	Tensor3(){}

	// Alternative Constructor
	Tensor3 (const Type & Val);

	// Copy Constructor
	Tensor3 (const Tensor3<Type,Dim> & Rgt);

	// Methods
	void SetWid        (int CellWidth);
	int  GetWid        () const;
	void Clear         ();
	Type GetEuclidNorm ();

	// Specific Methods
	void SetPermutation();

	// Operator Overloading
	void                      operator= (const Tensor3<Type,Dim> & Rgt);
	Tensor2<Type,Dim>       & operator[](int i);
	const Tensor2<Type,Dim> & operator[](int i) const;

	// Binary operators
	Tensor3<Type,Dim> operator+ (const Tensor3<Type,Dim> & Rgt) const;
	Tensor3<Type,Dim> operator- (const Tensor3<Type,Dim> & Rgt) const;
	Tensor3<Type,Dim> operator* (const Type & Rgt)              const;
	Tensor3<Type,Dim> operator/ (const Type & Rgt)              const;

private:
	Tensor2<Type,Dim> _tensors2[Dim];
};

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor3<Type, Dim> & T3);

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor3<Type, Dim> & T3);


/////////////////////////////////////////////////////////////////////////////////


// Alternative Constructor
template<typename Type, int Dim>
Tensor3<Type,Dim>::Tensor3 (const Type & Val)
{
	for (int i=0; i<Dim; ++i) 
		_tensors2[i] = Val;
}

// Copy Constructor
template<typename Type, int Dim>
Tensor3<Type,Dim>::Tensor3 (const Tensor3<Type,Dim> & Rgt)
{
	for (int i=0; i<Dim; ++i)
		_tensors2[i] = Rgt._tensors2[i];
}

// Methods
template<typename Type, int Dim>
void Tensor3<Type,Dim>::SetWid(int CellWidth)
{
	for (int i=0; i<Dim; ++i)
		_tensors2[i].SetWid(CellWidth);
}

template<typename Type, int Dim>
int Tensor3<Type,Dim>::GetWid() const
{
	return _tensors2[0].GetWid(); 
}

template<typename Type, int Dim>
void Tensor3<Type,Dim>::Clear()
{
	for (int i=0; i<Dim; ++i)
		_tensors2[i].Clear();
}

template<typename Type, int Dim>
Type Tensor3<Type,Dim>::GetEuclidNorm()
{
	Type sum = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i) 
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		sum = sum + _tensors2[i][j][k] * _tensors2[i][j][k];
	return static_cast<Type>(sqrt(sum));
}

// Specific Methods
template<typename Type, int Dim>
void Tensor3<Type,Dim>::SetPermutation()
{
	assert(Dim==3);
	for (int i=0; i<Dim; ++i)
		_tensors2[i].Clear();
	_tensors2[0][1][2] = static_cast<Type>(1);
	_tensors2[2][0][1] = static_cast<Type>(1);
	_tensors2[1][2][0] = static_cast<Type>(1);
	_tensors2[0][2][1] = static_cast<Type>(-1);
	_tensors2[1][0][2] = static_cast<Type>(-1);
	_tensors2[2][1][0] = static_cast<Type>(-1);
}

// Operator Overloading
template<typename Type, int Dim>
void Tensor3<Type,Dim>::operator= (const Tensor3<Type,Dim> & Rgt)
{
	assert (&Rgt!=this);
	for (int i=0; i<Dim; ++i) 
		_tensors2[i] = Rgt._tensors2[i];
}

template<typename Type, int Dim>
Tensor2<Type,Dim> & Tensor3<Type,Dim>::operator[] (int i)
{
	assert (i>=0 && i<Dim);
	return _tensors2[i];
}

template<typename Type, int Dim>
const Tensor2<Type,Dim> & Tensor3<Type,Dim>::operator[] (int i) const
{
	assert (i>=0 && i<Dim);
	return _tensors2[i];
}

// Binary operators
template<typename Type, int Dim>
Tensor3<Type,Dim> Tensor3<Type,Dim>::operator+ (const Tensor3<Type,Dim> & Rgt) const
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors2[i] + Rgt._tensors2[i];
	return res;
}

template<typename Type, int Dim>
Tensor3<Type,Dim> Tensor3<Type,Dim>::operator- (const Tensor3<Type,Dim> & Rgt) const
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors2[i] - Rgt._tensors2[i];
	return res;
}

template<typename Type, int Dim>
Tensor3<Type,Dim> Tensor3<Type,Dim>::operator* (const Type & Rgt) const
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors2[i] * Rgt;
	return res;
}

template<typename Type, int Dim>
Tensor3<Type,Dim> Tensor3<Type,Dim>::operator/ (const Type & Rgt) const
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors2[i] / Rgt;
	return res;
}

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor3<Type, Dim> & T3)
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		input >> T3[i][j][k];
	return input;
}

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor3<Type, Dim> & T3)
{
	for (int j=0; j<Dim; ++j)
	{
		for (int i=0; i<Dim; ++i)
		for (int k=0; k<Dim; ++k)
			output << std::setw(T3.GetWid()) << T3[i][j][k] << " ";
		if (j!=Dim-1) output << std::endl;
	}
	return output;
}

}; // namespace TensorsLib

#endif
