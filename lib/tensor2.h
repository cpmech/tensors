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

#ifndef TENSORS_TENSOR2_H
#define TENSORS_TENSOR2_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <vector>
#include "tensor1.h"

namespace TensorsLib
{

template<typename Type, int Dim>
class Tensor2
{
public:
	// Constructor
	Tensor2() : _maxima (false) {}

	// Alternative Constructor
	Tensor2 (const Type & Val);
	Tensor2 (const std::string & strVals);

	// Copy Constructor
	Tensor2 (const Tensor2<Type,Dim> & Rgt);

	// Methods
	void SetWid        (int CellWidth);
	int  GetWid        () const;
	void Clear         ();
	Type GetEuclidNorm () const;
	Type Norm          () const { return GetEuclidNorm(); }
	void SetMaxima     (bool Maxima=true) { _maxima = Maxima; }
	bool Maxima        () const           { return _maxima; }

	// Specific Methods
	void SetKronecker     ();
	void SetDiagonal      (Type Value);
	void GetTranspose     (Tensor2<Type,Dim> & T2)              const;
	void GetSymmetric     (Tensor2<Type,Dim> & T2)              const;
	void GetSkewSymmetric (Tensor2<Type,Dim> & T2)              const;
	void GetTensor1       (Tensor1<Type,Dim*Dim> & T1)          const;
	void GetMandel        (Tensor1<Type,Dim*Dim> & T1)          const;
	void GetMandelSym     (Tensor1<Type,( Dim*Dim+Dim)/2> & T1) const;
	void SetColumn        (int ColNum, const Tensor1<Type,Dim> & T1);
	void GetEigen         (std::vector<Type> & Values, std::vector< Tensor2<Type,Dim> > & Projectors) const;

	Type Trace            () const;
	Type Det              () const;
	Tensor2<Type,Dim> Inv () const;
	Tensor2<Type,Dim> Dev () const;

	// Operator Overloading
	void                      operator= (const Tensor2<Type,Dim> & Rgt);
	Tensor1<Type,Dim>       & operator[](int i);
	const Tensor1<Type,Dim> & operator[](int i) const;

	// Binary operators
	Tensor2<Type,Dim> operator+ (const Tensor2<Type,Dim> & Rgt) const;
	Tensor2<Type,Dim> operator- (const Tensor2<Type,Dim> & Rgt) const;
	Tensor2<Type,Dim> operator* (const Type & Rgt)              const;
	Tensor2<Type,Dim> operator/ (const Type & Rgt)              const;

	// Assign values separated by commas
	class CommaAssign
	{
	public:
		CommaAssign(Tensor1<Type,Dim> * Values, Type const & FirstValue) : _values(Values), _i(0), _j(0)
		{ 
			_values[_i][_j] = FirstValue;
		}
		CommaAssign & operator, (Type const & Num) 
		{
			if (_j==Dim-1) { _i++; _j=0; }
			else           { _j++;       }
			_values[_i][_j] = Num;
			return *this;
		}
	private:
		Tensor1<Type,Dim> * _values;
		int                 _i;
		int                 _j;
	};
	CommaAssign operator= (Type const & Num) { return CommaAssign(_tensors1, Num); }

protected:
	Tensor1<Type,Dim> _tensors1[Dim];

private:
	bool _maxima;
};

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor2<Type, Dim> & T2);

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor2<Type, Dim> & T2);


//////////////////////////////////////////////////////////////////////////////////


// Alternative Constructor
template<typename Type, int Dim>
Tensor2<Type,Dim>::Tensor2 (const Type & Val) : _maxima(false)
{
	for (int i=0; i<Dim; ++i) 
		_tensors1[i] = Val;
}
template<typename Type, int Dim>
Tensor2<Type,Dim>::Tensor2 (const std::string & strVals) : _maxima(false)
{
	std::istringstream iss(strVals);
	iss >> (*this);
}

// Copy Constructor
template<typename Type, int Dim>
Tensor2<Type,Dim>::Tensor2 (const Tensor2<Type,Dim> & Rgt)
{
	for (int i=0; i<Dim; ++i)
		_tensors1[i] = Rgt._tensors1[i];
}

// Methods
template<typename Type, int Dim>
void Tensor2<Type,Dim>::SetWid(int CellWidth)
{
	for (int i=0; i<Dim; ++i)
		_tensors1[i].SetWid(CellWidth);
}

template<typename Type, int Dim>
int Tensor2<Type,Dim>::GetWid() const
{
	return _tensors1[0].GetWid(); 
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::Clear()
{
	for (int i=0; i<Dim; ++i)
		_tensors1[i].Clear();
}

template<typename Type, int Dim>
Type Tensor2<Type,Dim>::GetEuclidNorm() const
{
	Type sum = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i) 
	for (int j=0; j<Dim; ++j)
		sum = sum + _tensors1[i][j] * _tensors1[i][j];
	return static_cast<Type>(sqrt(sum));
}

// Specific Methods
template<typename Type, int Dim>
void Tensor2<Type,Dim>::SetKronecker()
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	{
		if (i==j) _tensors1[i][j] = static_cast<Type>(1);
		else      _tensors1[i][j] = static_cast<Type>(0);
	}
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::SetDiagonal(Type Value)
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	{
		if (i==j) _tensors1[i][j] = Value;
		else      _tensors1[i][j] = static_cast<Type>(0);
	}
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetTranspose(Tensor2<Type,Dim> & T2) const
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		T2[i][j] = _tensors1[j][i];
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetSymmetric(Tensor2<Type,Dim> & T2) const
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		T2[i][j] = static_cast<Type>(0.5)*(_tensors1[i][j]+_tensors1[j][i]);
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetSkewSymmetric(Tensor2<Type,Dim> & T2) const
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		T2[i][j] = static_cast<Type>(0.5)*(_tensors1[i][j]-_tensors1[j][i]);
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetTensor1(Tensor1<Type,Dim*Dim> & T1) const
{
	int m=0;
	// Diagonal
	for (int i=0; i<Dim; ++i)
	{
		T1[m] = _tensors1[i][i];
		m++;
	}
	// Upper triangle
	for (int k=1; k<Dim; ++k)
	for (int i=0; i<Dim-k; ++i)
	{
		T1[m] = _tensors1[i][i+k];
		m++;
	}
	// Lower triangle
	for (int k=1; k<Dim; ++k)
	for (int j=0; j<Dim-k; ++j)
	{
		T1[m] = _tensors1[j+k][j];
		m++;
	}
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetMandel(Tensor1<Type,Dim*Dim> & T1) const
{
	Type sq2=sqrt(static_cast<Type>(2));
	int m=0;
	// Diagonal
	for (int i=0; i<Dim; ++i)
	{
		T1[m] = _tensors1[i][i];
		m++;
	}
	// Upper triangle
	for (int k=1; k<Dim; ++k)
	for (int i=0; i<Dim-k; ++i)
	{
		T1[m] = (_tensors1[i][i+k]+_tensors1[i+k][i])/sq2;
		m++;
	}
	// Lower triangle
	for (int k=1; k<Dim; ++k)
	for (int j=0; j<Dim-k; ++j)
	{
		T1[m] = (_tensors1[j+k][j]-_tensors1[j][j+k])/sq2;
		m++;
	}
}	

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetMandelSym(Tensor1<Type,(Dim*Dim+Dim)/2> & T1) const
{
	Type sq2=sqrt(static_cast<Type>(2));
	int m=0;
	// Diagonal
	for (int i=0; i<Dim; ++i)
	{
		T1[m] = _tensors1[i][i];
		m++;
	}
	// Upper triangle
	for (int k=1; k<Dim; ++k)
	for (int i=0; i<Dim-k; ++i)
	{
		T1[m] = sq2*_tensors1[i][i+k];
		m++;
	}
}	

template<typename Type, int Dim>
void Tensor2<Type,Dim>::SetColumn(int ColNum, const Tensor1<Type,Dim> & T1)
{
	assert(ColNum>=0);
	assert(ColNum<Dim);
	for (int i=0; i<Dim; ++i)
		_tensors1[i][ColNum] = T1[i];
}

template<typename Type, int Dim>
void Tensor2<Type,Dim>::GetEigen(std::vector<Type> & L, std::vector< Tensor2<Type,Dim> > & P) const
{
	// Check
	if (Dim!=3) throw "Tensor2::GetEigen: Tensor must have Dim==3";
	if ((_tensors1[0][1]!=_tensors1[1][0]) || (_tensors1[1][2]!=_tensors1[2][1]) || (_tensors1[0][2]!=_tensors1[2][0]))
		throw "Tensor2::GetEigen: Tensor must be symmetric";
	
	// Allocate arrays
	L.resize(3); // eigenvalues
	P.resize(3); // eigenprojectors
	Type  V0[3]; // eigenvector 0
	Type  V1[3]; // eigenvector 0
	Type  V2[3]; // eigenvector 0

	// JacobiRot
	{ // {{{
		const Type maxIt  = 30;      // Max number of iterations
		const Type errTol = 1.0e-15; // Erro: Tolerance
		const Type ZERO   = 1.0e-7;  // min value for t
		
		Type UT[3];         // Values of the Upper Triangle part of symmetric matrix A
		Type th;            // theta = (Aii-Ajj)/2Aij
		Type c;             // Cossine
		Type s;             // Sine
		Type cc;            // Cossine squared
		Type ss;            // Sine squared
		Type t;             // Tangent
		Type Temp;          // Auxiliar variable
		Type TM[3];         // Auxiliar array
		Type sumUT;         // Sum of upper triangle of abs(A) that measures the error
		int  it;            // Iteration number
		Type h;             // Difference L[i]-L[j]
		
		// Initialize eigenvalues which correspond to the diagonal part of A
		L[0]=_tensors1[0][0]; L[1]=_tensors1[1][1]; L[2]=_tensors1[2][2];

		// Initialize Upper Triangle part of A matrix (array[3])
		UT[0]=_tensors1[0][1]; UT[1]=_tensors1[1][2]; UT[2]=_tensors1[0][2];

		// Initialize eigenvectors
		V0[0]=1.0; V1[0]=0.0; V2[0]=0.0;
		V0[1]=0.0; V1[1]=1.0; V2[1]=0.0;
		V0[2]=0.0; V1[2]=0.0; V2[2]=1.0;

		// Iterations
		for (it=1; it<=maxIt; ++it)
		{ // {{{
			// Check error
			sumUT = fabs(UT[0])+fabs(UT[1])+fabs(UT[2]);
			if (sumUT<=errTol) break;
			
			// i=0, j=1 ,r=2 (p=3)
			h=L[0]-L[1];
			if (fabs(h)<ZERO) t=1.0;
			else
			{
				th=0.5*h/UT[0];
				t=1.0/(fabs(th)+sqrt(th*th+1.0));
				if (th<0.0) t=-t;
			}
			c  = 1.0/sqrt(1.0+t*t);
			s  = c*t;
			cc = c*c;
			ss = s*s;
			// Zeroes term UT[0]
			Temp  = cc*L[0] + 2.0*c*s*UT[0] + ss*L[1];
			L[1]  = ss*L[0] - 2.0*c*s*UT[0] + cc*L[1];
			L[0]  = Temp;
			UT[0] = 0.0;
			Temp  = c*UT[2] + s*UT[1];
			UT[1] = c*UT[1] - s*UT[2];
			UT[2] = Temp;
			// Actualize eigenvectors
			TM[0] = s*V1[0] + c*V0[0];
			TM[1] = s*V1[1] + c*V0[1];
			TM[2] = s*V1[2] + c*V0[2];
			V1[0] = c*V1[0] - s*V0[0];
			V1[1] = c*V1[1] - s*V0[1];
			V1[2] = c*V1[2] - s*V0[2];
			V0[0] = TM[0];
			V0[1] = TM[1];
			V0[2] = TM[2];
			
			// i=1, j=2 ,r=0 (p=4)
			h = L[1]-L[2];
			if (fabs(h)<ZERO) t=1.0;
			else
			{
				th=0.5*h/UT[1];
				t=1.0/(fabs(th)+sqrt(th*th+1.0));
				if (th<0.0) t=-t;
			}
			c  = 1.0/sqrt(1.0+t*t);
			s  = c*t;
			cc = c*c;
			ss = s*s;
			// Zeroes term UT[1]
			Temp  = cc*L[1] + 2.0*c*s*UT[1] + ss*L[2];
			L[2]  = ss*L[1] - 2.0*c*s*UT[1] + cc*L[2];
			L[1]  = Temp;
			UT[1] = 0.0;
			Temp  = c*UT[0] + s*UT[2];
			UT[2] = c*UT[2] - s*UT[0];
			UT[0] = Temp;
			// Actualize eigenvectors
			TM[1] = s*V2[1] + c*V1[1];
			TM[2] = s*V2[2] + c*V1[2];
			TM[0] = s*V2[0] + c*V1[0];
			V2[1] = c*V2[1] - s*V1[1];
			V2[2] = c*V2[2] - s*V1[2];
			V2[0] = c*V2[0] - s*V1[0];
			V1[1] = TM[1];
			V1[2] = TM[2];
			V1[0] = TM[0];

			// i=0, j=2 ,r=1 (p=5)
			h = L[0]-L[2];
			if (fabs(h)<ZERO) t=1.0;
			else
			{
				th=0.5*h/UT[2];
				t=1.0/(fabs(th)+sqrt(th*th+1.0));
				if (th<0.0) t=-t;
			}
			c  = 1.0/sqrt(1.0+t*t);
			s  = c*t;
			cc = c*c;
			ss = s*s;
			// Zeroes term UT[2]
			Temp  = cc*L[0] + 2.0*c*s*UT[2] + ss*L[2];
			L[2]  = ss*L[0] - 2.0*c*s*UT[2] + cc*L[2];
			L[0]  = Temp;
			UT[2] = 0.0;
			Temp  = c*UT[0] + s*UT[1];
			UT[1] = c*UT[1] - s*UT[0];
			UT[0] = Temp;
			// Actualize eigenvectors
			TM[0] = s*V2[0] + c*V0[0];
			TM[2] = s*V2[2] + c*V0[2];
			TM[1] = s*V2[1] + c*V0[1];
			V2[0] = c*V2[0] - s*V0[0];
			V2[2] = c*V2[2] - s*V0[2];
			V2[1] = c*V2[1] - s*V0[1];
			V0[0] = TM[0];
			V0[2] = TM[2];
			V0[1] = TM[1];
		} // iterations - end }}}
		if (it==maxIt) throw "Tensor2::GetEigen: Did not converge";
	} // JacobiRot - end }}}

	// Calculate eigenprojectors (Pk <- Vk dyad Vk, no sum on k)
	for (int i=0; i<3; ++i)
	for (int j=0; j<3; ++j)
	{
		P[0][i][j] = V0[i]*V0[j];
		P[1][i][j] = V1[i]*V1[j];
		P[2][i][j] = V2[i]*V2[j];
	}
}

template<typename Type, int Dim>
Type Tensor2<Type,Dim>::Trace() const
{
	Type tr = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i)
		tr = tr + _tensors1[i][i];
	return tr;
}

template<typename Type, int Dim>
Type Tensor2<Type,Dim>::Det() const
{
	if (Dim!=3) throw "Tensor2::Determinant: Tensor must have Dim==3";
	return   _tensors1[0][0]*(_tensors1[1][1]*_tensors1[2][2] - _tensors1[1][2]*_tensors1[2][1]) \
		   - _tensors1[0][1]*(_tensors1[1][0]*_tensors1[2][2] - _tensors1[1][2]*_tensors1[2][0]) \
		   + _tensors1[0][2]*(_tensors1[1][0]*_tensors1[2][1] - _tensors1[1][1]*_tensors1[2][0]);
}

template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::Inv() const
{
	if (Dim!=3) throw "Tensor2::GetInverse: Tensor must have Dim==3";
	Tensor2<Type,Dim> inv;
	Type det = this->Det();
	if (det==static_cast<Type>(0)) throw "Tensor2::GetInverse: Determinant must be non-null";

	inv[0][0] = (_tensors1[1][1]*_tensors1[2][2] - _tensors1[1][2]*_tensors1[2][1]) / det;
	inv[0][1] = (_tensors1[0][2]*_tensors1[2][1] - _tensors1[0][1]*_tensors1[2][2]) / det;
	inv[0][2] = (_tensors1[0][1]*_tensors1[1][2] - _tensors1[0][2]*_tensors1[1][1]) / det;

	inv[1][0] = (_tensors1[1][2]*_tensors1[2][0] - _tensors1[1][0]*_tensors1[2][2]) / det;
	inv[1][1] = (_tensors1[0][0]*_tensors1[2][2] - _tensors1[0][2]*_tensors1[2][0]) / det;
	inv[1][2] = (_tensors1[0][2]*_tensors1[1][0] - _tensors1[0][0]*_tensors1[1][2]) / det;

	inv[2][0] = (_tensors1[1][0]*_tensors1[2][1] - _tensors1[1][1]*_tensors1[2][0]) / det;
	inv[2][1] = (_tensors1[0][1]*_tensors1[2][0] - _tensors1[0][0]*_tensors1[2][1]) / det;
	inv[2][2] = (_tensors1[0][0]*_tensors1[1][1] - _tensors1[0][1]*_tensors1[1][0]) / det;

	return inv;
}

template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::Dev() const
{
	Tensor2<Type,Dim> dev = (*this);
	Type tr_by3 = this->Trace()/static_cast<Type>(3);
	for (int i=0; i<Dim; ++i)
		dev[i][i] = _tensors1[i][i] - tr_by3;
	return dev;
}

// Operator Overloading
template<typename Type, int Dim>
void Tensor2<Type,Dim>::operator= (const Tensor2<Type,Dim> & Rgt)
{
	assert (&Rgt!=this);
	for (int i=0; i<Dim; ++i) 
		_tensors1[i] = Rgt._tensors1[i];
}

template<typename Type, int Dim>
Tensor1<Type,Dim> & Tensor2<Type,Dim>::operator[] (int i)
{
	assert (i>=0 && i<Dim);
	return _tensors1[i];
}

template<typename Type, int Dim>
const Tensor1<Type,Dim> & Tensor2<Type,Dim>::operator[] (int i) const
{
	assert (i>=0 && i<Dim);
	return _tensors1[i];
}

// Binary operators
template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::operator+ (const Tensor2<Type,Dim> & Rgt) const
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors1[i] + Rgt._tensors1[i];
	return res;
}

template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::operator- (const Tensor2<Type,Dim> & Rgt) const
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors1[i] - Rgt._tensors1[i];
	return res;
}

template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::operator* (const Type & Rgt) const
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors1[i] * Rgt;
	return res;
}

template<typename Type, int Dim>
Tensor2<Type,Dim> Tensor2<Type,Dim>::operator/ (const Type & Rgt) const
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i) 
		res[i] = _tensors1[i] / Rgt;
	return res;
}

// Input: Raw data
template<typename Type, int Dim>
std::istream & operator>> (std::istream & input, Tensor2<Type, Dim> & T2)
{
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		input >> T2[i][j];
	return input;
}

// Output: Table formatted
template<typename Type, int Dim>
std::ostream & operator<< (std::ostream & output, const Tensor2<Type, Dim> & T2)
{
	if (T2.Maxima())
	{
		output << "matrix(";
		for (int i=0; i<Dim; ++i)
		{
			output << "[";
			for (int j=0; j<Dim; ++j)
			{
				output << std::setw(T2.GetWid()) << T2[i][j];
				if (j!=Dim-1) output << ",";
			}
			if (i!=Dim-1) output << "],";
			else          output << "]";
		}
		output << "), ratsimp;" << std::endl;
	}
	else
	{
		for (int i=0; i<Dim; ++i)
		{
			for (int j=0; j<Dim; ++j)
				output << std::setw(T2.GetWid()) << T2[i][j] << " ";
			if (i!=Dim-1) output << std::endl;
		}
	}
	return output;
}

}; // namespace TensorsLib

#endif

// vim:fdm=marker
