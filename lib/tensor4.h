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

#ifndef TENSORS_TENSOR4_H
#define TENSORS_TENSOR4_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "tensor3.h"

namespace TensorsLib
{

template<typename Type, int Dim>
class Tensor4
{
public:
	// Constructor 
	Tensor4() : _print_bars(true) {}

	// Alternative Constructor
	Tensor4 (const Type & Val);

	// Copy Constructor
	Tensor4 (const Tensor4<Type,Dim> & Rgt);

	// Methods
	void SetPrintBars  (bool PrintBars) { _print_bars = PrintBars; }
	bool GetPrintBars  () const         { return _print_bars; }
	void SetWid        (int CellWidth);
	int  GetWid        () const;
	void Clear         ();
	Type GetEuclidNorm ();

	// Specific Methods
	void SetGeneralIsotropic (Type Alp, Type Bet, Type Gam);
	void SetIso              ();
	void SetSym              ();
	void SetSymDev           ();
	void SetSkew             ();
	void GetTensor2          (Tensor2<Type,Dim*Dim> & T2)         const;
	void GetMandel           (Tensor2<Type,Dim*Dim> & T2)         const;
	void GetMandelSym        (Tensor2<Type,(Dim*Dim+Dim)/2> & T2) const;

	// Operator Overloading
	void                      operator= (const Tensor4<Type,Dim> & Rgt);
	Tensor3<Type,Dim>       & operator[](int i);
	const Tensor3<Type,Dim> & operator[](int i) const;

	// Binary operators
	Tensor4<Type,Dim> operator+ (const Tensor4<Type,Dim> & Rgt) const;
	Tensor4<Type,Dim> operator- (const Tensor4<Type,Dim> & Rgt) const;
	Tensor4<Type,Dim> operator* (const Type & Rgt)              const;
	Tensor4<Type,Dim> operator/ (const Type & Rgt)              const;

private:
	bool              _print_bars;
	Tensor3<Type,Dim> _tensors3[Dim];
};

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor4<Type, Dim> & T4);

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor4<Type, Dim> & T4);


/////////////////////////////////////////////////////////////////////////////////


// Alternative Constructor
template<typename Type, int Dim>
Tensor4<Type,Dim>::Tensor4 (const Type & Val) : _print_bars(true)
{
	for (int i=0; i<Dim; ++i) 
		_tensors3[i] = Val;
}

// Copy Constructor
template<typename Type, int Dim>
Tensor4<Type,Dim>::Tensor4 (const Tensor4<Type,Dim> & Rgt) : _print_bars(true)
{
	for (int i=0; i<Dim; ++i)
		_tensors3[i] = Rgt._tensors3[i];
}

// Methods
template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetWid(int CellWidth)
{
	for (int i=0; i<Dim; ++i)
		_tensors3[i].SetWid(CellWidth);
}

template<typename Type, int Dim>
int  Tensor4<Type,Dim>::GetWid() const
{
	return _tensors3[0].GetWid(); 
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::Clear()
{
	for (int i=0; i<Dim; ++i)
		_tensors3[i].Clear();
}

template<typename Type, int Dim>
Type Tensor4<Type,Dim>::GetEuclidNorm()
{
	Type sum = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i) 
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		sum = sum + _tensors3[i][j][k][l] * _tensors3[i][j][k][l];
	return static_cast<Type>(sqrt(sum));
}

// Specific Methods
template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetGeneralIsotropic(Type Alp, Type Bet, Type Gam)
{
	Tensor2<Type,Dim> del;
	del.SetKronecker();
	for (int i=0; i<Dim; ++i) 
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		_tensors3[i][j][k][l] =   Alp*del[i][j]*del[k][l]
			                    + Bet*del[i][k]*del[j][l]
								+ Gam*del[i][l]*del[j][k];
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetIso()
{
	SetGeneralIsotropic(static_cast<Type>(1)/static_cast<Type>(3),
			            static_cast<Type>(0),
						static_cast<Type>(0));
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetSym()
{
	SetGeneralIsotropic(static_cast<Type>(0),
			            static_cast<Type>(1)/static_cast<Type>(2),
						static_cast<Type>(1)/static_cast<Type>(2));
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetSymDev()
{
	SetGeneralIsotropic(static_cast<Type>(-1)/static_cast<Type>(3),
			            static_cast<Type>(1)/static_cast<Type>(2),
			            static_cast<Type>(1)/static_cast<Type>(2));
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::SetSkew()
{
	SetGeneralIsotropic(static_cast<Type>(0),
			            static_cast<Type>(1)/static_cast<Type>(2),
						static_cast<Type>(-1)/static_cast<Type>(2));
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::GetTensor2(Tensor2<Type,Dim*Dim> & T2) const
{
	int m=0;
	// Diagonal
	for (int i=0; i<Dim; ++i)
	{
		_tensors3[i][i].GetTensor1(T2[m]);
		m++;
	}
	// Upper triangle
	for (int k=1; k<Dim; ++k)
	for (int i=0; i<Dim-k; ++i)
	{
		_tensors3[i][i+k].GetTensor1(T2[m]);
		m++;
	}
	// Lower triangle
	for (int k=1; k<Dim; ++k)
	for (int j=0; j<Dim-k; ++j)
	{
		_tensors3[j+k][j].GetTensor1(T2[m]);
		m++;
	}
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::GetMandel(Tensor2<Type,Dim*Dim> & T2) const
{
	// Mandel orthonormal basis
	Type    one_sq2=static_cast<Type>(1) /sqrt(static_cast<Type>(2));
	Type negOne_sq2=static_cast<Type>(-1)/sqrt(static_cast<Type>(2));
	Tensor2<Type,Dim> g[Dim][Dim];
	// Diagonal
	for (int i=0; i<Dim; ++i)
		g[i][i] [i][i] = static_cast<Type>(1);
	// Upper triangle
	for (int k=1; k<Dim; ++k)
	for (int i=0; i<Dim-k; ++i)
	{
		g[i][i+k] [i][i+k] = one_sq2;
		g[i][i+k] [i+k][i] = one_sq2;
	}
	// Lower triangle
	for (int k=1; k<Dim; ++k)
	for (int j=0; j<Dim-k; ++j)
	{
		g[j+k][j] [j+k][j] =    one_sq2;
		g[j+k][j] [j][j+k] = negOne_sq2;
	}

	// Components
	Tensor4<Type,Dim> T4;
	Tensor2<Type,Dim> tmp;
	Type              res;
	for (int p=0; p<Dim; ++p)
	for (int q=0; q<Dim; ++q)
	for (int r=0; r<Dim; ++r)
	for (int s=0; s<Dim; ++s)
	{
		// tmp := g[p][q] % this
		tmp.Clear();
		for (int k=0; k<Dim; ++k)
		for (int l=0; l<Dim; ++l)
			for (int i=0; i<Dim; ++i)
			for (int j=0; j<Dim; ++j)
				tmp[k][l] = tmp[k][l] + g[p][q] [i][j] * _tensors3[i][j][k][l];
		// res := tmp % g[r][s]
		res = static_cast<Type>(0);
		for (int i=0; i<Dim; ++i)
			for (int j=0; j<Dim; ++j)
				res = res + tmp[i][j] * g[r][s] [i][j];
		T4[p][q][r][s] = res;
	}
	// Result
	T4.GetTensor2(T2);
}

template<typename Type, int Dim>
void Tensor4<Type,Dim>::GetMandelSym(Tensor2<Type,(Dim*Dim+Dim)/2> & T2) const
{
	Tensor2<Type,Dim*Dim> tmp;
	GetMandel(tmp);
	for (int i=0; i<(Dim*Dim+Dim)/2; ++i)
	for (int j=0; j<(Dim*Dim+Dim)/2; ++j)
		T2[i][j] = tmp[i][j];
}

// Operator Overloading
template<typename Type, int Dim>
void Tensor4<Type,Dim>::operator= (const Tensor4<Type,Dim> & Rgt)
{
	assert (&Rgt!=this);
	for (int i=0; i<Dim; ++i) 
		_tensors3[i] = Rgt._tensors3[i];
}

template<typename Type, int Dim>
Tensor3<Type,Dim> & Tensor4<Type,Dim>::operator[] (int i)
{
	assert (i>=0 && i<Dim);
	return _tensors3[i];
}

template<typename Type, int Dim>
const Tensor3<Type,Dim> & Tensor4<Type,Dim>::operator[] (int i) const
{
	assert (i>=0 && i<Dim);
	return _tensors3[i];
}

// Binary operators
template<typename Type, int Dim>
Tensor4<Type,Dim> Tensor4<Type,Dim>::operator+ (const Tensor4<Type,Dim> & Rgt) const
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors3[i] + Rgt._tensors3[i];
	return res;
}

template<typename Type, int Dim>
Tensor4<Type,Dim> Tensor4<Type,Dim>::operator- (const Tensor4<Type,Dim> & Rgt) const
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors3[i] - Rgt._tensors3[i];
	return res;
}

template<typename Type, int Dim>
Tensor4<Type,Dim> Tensor4<Type,Dim>::operator* (const Type & Rgt) const
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors3[i] * Rgt;
	return res;
}

template<typename Type, int Dim>
Tensor4<Type,Dim> Tensor4<Type,Dim>::operator/ (const Type & Rgt) const
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors3[i] / Rgt;
	return res;
}

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor4<Type, Dim> & T4)
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		input >> T4[i][j][k][l];
	return input;
}

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor4<Type, Dim> & T4)
{
	for (int i=0; i<Dim; ++i)
	{
		for (int k=0; k<Dim; ++k)
		{
			for (int j=0; j<Dim; ++j)
			{
				for (int l=0; l<Dim; ++l)
					output << std::setw(T4.GetWid()) << T4[i][j][k][l] << " ";
				if (T4.GetPrintBars())
					if (j!=Dim-1) output << "| ";
			}
			if (!(i==Dim-1 && k==Dim-1)) output << std::endl;
		}
		if (T4.GetPrintBars())
		{
			if (i!=Dim-1)
			{
				for (int p=0; p<Dim*Dim*(T4.GetWid()+1)-1+(Dim-1)*2; ++p)
					output << "-";
				output << std::endl;
			}
		}
	}
	return output;
}

}; // namespace TensorsLib

#endif
