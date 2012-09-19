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

#ifndef TENSORS_OPERATORS_H
#define TENSORS_OPERATORS_H

// Std Lib
#include <stdio.h>

#include "tensor1.h"
#include "tensor2.h"
#include "tensor3.h"
#include "tensor4.h"

namespace TensorsLib
{

int MandelToTensor2_i[6]    = {0,1,2, 0,1,2};
int MandelToTensor2_j[6]    = {0,1,2, 1,2,0};
int Tensor2ToMandel_i[3][3] = {{0,3,5},
                               {3,1,4},
                               {5,4,2}};

int Tensor4ToMandel_i[3][3][3][3]= 
{{{{0,0,0},{0,0,0},{0,0,0}}, {{3,3,3},{3,3,3},{3,3,3}}, {{5,5,5},{5,5,5},{5,5,5}}},
 {{{3,3,3},{3,3,3},{3,3,3}}, {{1,1,1},{1,1,1},{1,1,1}}, {{4,4,4},{4,4,4},{4,4,4}}},
 {{{5,5,5},{5,5,5},{5,5,5}}, {{4,4,4},{4,4,4},{4,4,4}}, {{2,2,2},{2,2,2},{2,2,2}}}};

int Tensor4ToMandel_j[3][3][3][3]=
{{{{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}},
 {{{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}},
 {{{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}, {{0,3,5},{3,1,4},{5,4,2}}}};

void PrintMapping ()
{
    char line[256];
	for (int i=0; i<3; ++i)
    {
        if (i==0) sprintf(line,"{{");
        else      sprintf(line," {");
        for (int j=0; j<3; ++j)
        {
            sprintf(line,"%s{",line);
            for (int k=0; k<3; ++k)
            {
                sprintf(line,"%s{",line);
                for (int l=0; l<3; ++l)
                {
                    if (l<2) sprintf(line,"%s%d%d,",line, Tensor2ToMandel_i[i][j], Tensor2ToMandel_i[k][l]);
                    else     sprintf(line,"%s%d%d", line, Tensor2ToMandel_i[i][j], Tensor2ToMandel_i[k][l]);
                }
                if (k<2) sprintf(line,"%s},",line);
                else     sprintf(line,"%s}", line);
            }
            if (j<2) sprintf(line,"%s}, ",line);
            else     sprintf(line,"%s}",  line);
        }
        if (i<2) sprintf(line,"%s},", line);
        else     sprintf(line,"%s}};",line);
        printf("%s\n",line);
    }
}

// --------------------------------------------------------------- operator *  =>  dot

// 1.#)

// 1.1) r = sum(i=1,Dim){ L[i] * R[i] }                             scalar = T1 dot T1
template<typename Type, int Dim>
Type operator* (const Tensor1<Type,Dim> & Lft, const Tensor1<Type,Dim> & Rgt) 
{
	Type res = static_cast<Type>(0);
 	for (int i=0; i<Dim; ++i)
		res = res + Lft[i] * Rgt[i];
	return res;
}

// 1.2) R[j] = sum(i=1,Dim){ L[i] * R[i][j] }                           T1 = T1 dot T2
template<typename Type, int Dim>
Tensor1<Type,Dim> operator* (const Tensor1<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt) 
{
	Tensor1<Type,Dim> res;
	for (int j=0; j<Dim; ++j)
		for (int i=0; i<Dim; ++i)
			res[j] = res[j] + Lft[i] * Rgt[i][j];
	return res;
}

// 1.3) R[j][k] = sum(i=1,Dim){ L[i] * R[i][j][k] }                     T2 = T1 dot T3
template<typename Type, int Dim>
Tensor2<Type,Dim> operator* (const Tensor1<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt) 
{
	Tensor2<Type,Dim> res;
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		for (int i=0; i<Dim; ++i)
			res[j][k] = res[j][k] + Lft[i] * Rgt[i][j][k];
	return res;
}

// 1.4) R[j][k][l] = sum(i=1,Dim){ L[i] * R[i][j][k][l] }               T3 = T1 dot T4
template<typename Type, int Dim>
Tensor3<Type,Dim> operator* (const Tensor1<Type,Dim> &Lft, const Tensor4<Type,Dim> &Rgt) 
{
	Tensor3<Type,Dim> res;
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		for (int i=0; i<Dim; ++i)
			res[j][k][l] = res[j][k][l] + Lft[i] * Rgt[i][j][k][l];
	return res;
}

// 2.#)

// 2.1) R[i] = sum(j=1,Dim){ L[i][j] * R[j] }                           T1 = T2 dot T1
template<typename Type, int Dim>
Tensor1<Type,Dim> operator* (const Tensor2<Type,Dim> &Lft, const Tensor1<Type,Dim> &Rgt) 
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
		for (int j=0; j<Dim; ++j)
			res[i] = res[i] + Lft[i][j] * Rgt[j];
	return res;
}

// 2.2) R[i][k] = sum(j=1,Dim){ L[i][j] * R[j][k] }                     T2 = T2 dot T2
template<typename Type, int Dim>
Tensor2<Type,Dim> operator* (const Tensor2<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt) 
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int k=0; k<Dim; ++k)
		for (int j=0; j<Dim; ++j)
			res[i][k] = res[i][k] + Lft[i][j] * Rgt[j][k];
	return res;
}

// 2.3) R[i][k][l] = sum(j=1,Dim){ L[i][j] * R[j][k][l] }               T3 = T2 dot T3
template<typename Type, int Dim>
Tensor3<Type,Dim> operator* (const Tensor2<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt) 
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		for (int j=0; j<Dim; ++j)
			res[i][k][l] = res[i][k][l] + Lft[i][j] * Rgt[j][k][l];
	return res;
}

// 2.4) R[i][k][l][m] = sum(j=1,Dim){L[i][j] * R[j][k][l][m]}           T4 = T2 dot T4
template<typename Type, int Dim>
Tensor4<Type,Dim> operator* (const Tensor2<Type,Dim> &Lft, const Tensor4<Type,Dim> &Rgt) 
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
	for (int m=0; m<Dim; ++m)
		for (int j=0; j<Dim; ++j)
			res[i][k][l][m] = res[i][k][l][m] + Lft[i][j] * Rgt[j][k][l][m];
	return res;
}

// 3.#)

// 3.1) R[i][j] = sum(k=1,Dim){ L[i][j][k] * R[k] }                     T2 = T3 dot T1
template<typename Type, int Dim>
Tensor2<Type,Dim> operator* (const Tensor3<Type,Dim> &Lft, const Tensor1<Type,Dim> &Rgt) 
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		for (int k=0; k<Dim; ++k)
			res[i][j] = res[i][j] + Lft[i][j][k] * Rgt[k];
	return res;
}

// 3.2) R[i][j][l] = sum(k=1,Dim){ L[i][j][k] * R[k][l] }               T3 = T3 dot T2
template<typename Type, int Dim>
Tensor3<Type,Dim> operator* (const Tensor3<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt) 
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int l=0; l<Dim; ++l)
		for (int k=0; k<Dim; ++k)
			res[i][j][l] = res[i][j][l] + Lft[i][j][k] * Rgt[k][l];
	return res;
}

// 3.3) R[i][j][l][m] = sum(k=1,Dim){L[i][j][k] * R[k][l][m]}           T4 = T3 dot T3
template<typename Type, int Dim>
Tensor4<Type,Dim> operator* (const Tensor3<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt) 
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int l=0; l<Dim; ++l)
	for (int m=0; m<Dim; ++m)
		for (int k=0; k<Dim; ++k)
			res[i][j][l][m] = res[i][j][l][m] + Lft[i][j][k] * Rgt[k][l][m];
	return res;
}

// 4.#)

// 4.1) R[i][j][k] = sum(l=1,Dim){ L[i][j][k][l] * R[l] }               T3 = T4 dot T1
template<typename Type, int Dim>
Tensor3<Type,Dim> operator* (const Tensor4<Type,Dim> &Lft, const Tensor1<Type,Dim> &Rgt) 
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		for (int l=0; l<Dim; ++l)
			res[i][j][k] = res[i][j][k] + Lft[i][j][k][l] * Rgt[l];
	return res;
}

// 4.2) R[i][j][k][m] = sum(l=1,Dim){L[i][j][k][l] * R[l][m]}           T4 = T4 dot T2
template<typename Type, int Dim>
Tensor4<Type,Dim> operator* (const Tensor4<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt) 
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int m=0; m<Dim; ++m)
		for (int l=0; l<Dim; ++l)
			res[i][j][k][m] = res[i][j][k][m] + Lft[i][j][k][l] * Rgt[l][m];
	return res;
}

// -------------------------------------------------------- operator %  =>  double-dot

// 2.#)

// 2.2) r = sum(i=1,Dim) sum(j=1,Dim) { L[i][j]*R[i][j] }         scalar = T2 d-dot T2
template<typename Type, int Dim>
Type operator% (const Tensor2<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Type res = static_cast<Type>(0);
	for (int i=0; i<Dim; ++i)
		for (int j=0; j<Dim; ++j)
			res = res + Lft[i][j] * Rgt[i][j];
	return res;
}

// 2.3) R[k] = sum(i=1,Dim) sum(j=1,Dim) { L[i][j]*R[i][j][k] }       T1 = T2 d-dot T3
template<typename Type, int Dim>
Tensor1<Type,Dim> operator% (const Tensor2<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt)
{
	Tensor1<Type,Dim> res;
	for (int k=0; k<Dim; ++k)
		for (int i=0; i<Dim; ++i)
		for (int j=0; j<Dim; ++j)
			res[k] = res[k] + Lft[i][j] * Rgt[i][j][k];
	return res;
}

// 2.4) R[k][l] = sum(i=1,Dim) sum(j=1,Dim) { L[i][j]*R[i][j][k][l] } T2 = T2 d-dot T4
template<typename Type, int Dim>
Tensor2<Type,Dim> operator% (const Tensor2<Type,Dim> &Lft, const Tensor4<Type,Dim> &Rgt)
{
	Tensor2<Type,Dim> res;
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		for (int i=0; i<Dim; ++i)
		for (int j=0; j<Dim; ++j)
			res[k][l] = res[k][l] + Lft[i][j] * Rgt[i][j][k][l];
	return res;
}

// 3.#)

// 3.2) R[i] = sum(j=1,Dim) sum(k=1,Dim) { L[i][j][k]*R[j][k] }       T1 = T3 d-dot T2
template<typename Type, int Dim>
Tensor1<Type,Dim> operator% (const Tensor3<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor1<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
		for (int j=0; j<Dim; ++j)
		for (int k=0; k<Dim; ++k)
			res[i] = res[i] + Lft[i][j][k] * Rgt[j][k];
	return res;
}

// 3.3) R[i][l] = sum(j=1,Dim) sum(k=1,Dim) { L[i][j][k]*R[j][k][l] }
//                                                                    T2 = T3 d-dot T3
template<typename Type, int Dim>
Tensor2<Type,Dim> operator% (const Tensor3<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt)
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int l=0; l<Dim; ++l)
		for (int j=0; j<Dim; ++j)
		for (int k=0; k<Dim; ++k)
			res[i][l] = res[i][l] + Lft[i][j][k] * Rgt[j][k][l];
	return res;
}

// 3.4) R[i][l][m] = sum(j=1,Dim) sum(k=1,Dim) { L[i][j][k]*R[j][k][l][m] }
//                                                                    T3 = T3 d-dot T4
template<typename Type, int Dim>
Tensor3<Type,Dim> operator% (const Tensor3<Type,Dim> &Lft, const Tensor4<Type,Dim> &Rgt)
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int l=0; l<Dim; ++l)
	for (int m=0; m<Dim; ++m)
		for (int j=0; j<Dim; ++j)
		for (int k=0; k<Dim; ++k)
			res[i][l][m] = res[i][l][m] + Lft[i][j][k] * Rgt[j][k][l][m];
	return res;
}

// 4.#)

// 4.2) R[i][j] = sum(k=1,Dim) sum(l=1,Dim){ L[i][j][k][l] * R[k][l] }
//                                                                    T2 = T4 d-dot T2
template<typename Type, int Dim>
Tensor2<Type,Dim> operator% (const Tensor4<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		for (int k=0; k<Dim; ++k)
		for (int l=0; l<Dim; ++l)
			res[i][j] = res[i][j] + Lft[i][j][k][l] * Rgt[k][l];
	return res;
}

// 4.3) R[i][j][m] = sum(k=1,Dim) sum(l=1,Dim){ L[i][j][k][l] * R[k][l][m] }
//                                                                    T3 = T4 d-dot T3
template<typename Type, int Dim>
Tensor3<Type,Dim> operator% (const Tensor4<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt)
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int m=0; m<Dim; ++m)
		for (int k=0; k<Dim; ++k)
		for (int l=0; l<Dim; ++l)
			res[i][j][m] = res[i][j][m] + Lft[i][j][k][l] * Rgt[k][l][m];
	return res;
}

// 4.4) R[i][j][m][n] = sum(k=1,Dim)sum(l=1,Dim){L[i][j][k][l]*R[k][l][m][n]}
//                                                                    T4 = T4 d-dot T4
template<typename Type, int Dim>
Tensor4<Type,Dim> operator% (const Tensor4<Type,Dim> &Lft, const Tensor4<Type,Dim> &Rgt)
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int m=0; m<Dim; ++m)
	for (int n=0; n<Dim; ++n)
		for (int k=0; k<Dim; ++k)
		for (int l=0; l<Dim; ++l)
			res[i][j][m][n]=res[i][j][m][n]+Lft[i][j][k][l]*Rgt[k][l][m][n];
	return res;
}

// ------------------------------------------------------------ operator &  =>  dyadic

// 1.#)

// 1.1) R[i][j] = L[i]*R[j]                                              T2 = T1 dy T1
template<typename Type, int Dim>
Tensor2<Type,Dim> operator& (const Tensor1<Type,Dim> &Lft, const Tensor1<Type,Dim> &Rgt)
{
	Tensor2<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
		res[i][j] = Lft[i] * Rgt[j];
	return res;
}

// 1.2) R[i][j][k] = L[i]*R[j][k]                                        T3 = T1 dy T2
template<typename Type, int Dim>
Tensor3<Type,Dim> operator& (const Tensor1<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		res[i][j][k] = Lft[i] * Rgt[j][k];
	return res;
}

// 1.3) R[i][j][k][l] = L[i]*R[j][k][l]                                  T4 = T1 dy T3
template<typename Type, int Dim>
Tensor4<Type,Dim> operator& (const Tensor1<Type,Dim> &Lft, const Tensor3<Type,Dim> &Rgt)
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		res[i][j][k][l] = Lft[i] * Rgt[j][k][l];
	return res;
}

// 2.#)

// 2.1) R[i][j][k] = L[i][j]*R[k]                                        T3 = T2 dy T1
template<typename Type, int Dim>
Tensor3<Type,Dim> operator& (const Tensor2<Type,Dim> &Lft, const Tensor1<Type,Dim> &Rgt)
{
	Tensor3<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
		res[i][j][k] = Lft[i][j] * Rgt[k];
	return res;
}

// 2.2) R[i][j][k][l] = L[i][j]*R[k][l]                                  T4 = T2 dy T2
template<typename Type, int Dim>
Tensor4<Type,Dim> operator& (const Tensor2<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		res[i][j][k][l] = Lft[i][j] * Rgt[k][l];
	return res;
}

// ------------------------------------------------------- operator ^  =>  leaf-dyadic

// 2.#)

// 2.2) R[i][j][k][l] = L[i][k]*R[j][l]                             T4 = T2 leaf-dy T2
template<typename Type, int Dim>
Tensor4<Type,Dim> operator^ (const Tensor2<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		res[i][j][k][l] = Lft[i][k] * Rgt[j][l];
	return res;
}

// ------------------------------------------------------- operator |  =>  palm-dyadic

// 2.#)

// 2.2) R[i][j][k][l] = L[i][l]*R[j][k]                             T4 = T2 palm-dy T2
template<typename Type, int Dim>
Tensor4<Type,Dim> operator| (const Tensor2<Type,Dim> &Lft, const Tensor2<Type,Dim> &Rgt)
{
	Tensor4<Type,Dim> res;
	for (int i=0; i<Dim; ++i)
	for (int j=0; j<Dim; ++j)
	for (int k=0; k<Dim; ++k)
	for (int l=0; l<Dim; ++l)
		res[i][j][k][l] = Lft[i][l] * Rgt[j][k];
	return res;
}

//////////////////////////////////////////////////////////////////////////// Functions 

/** Trace. */
template<typename Type, int Dim>
inline Type Tr (Tensor2<Type,Dim> const & A)
{
    Type res = static_cast<Type>(0);
    for (int i=0; i<Dim; ++i)
    for (int j=0; j<Dim; ++j)
    {
        if (i==j) res += A[i][j];
    }
    return res;
}

/** Characteristic invariants. */
template<typename Type, int Dim>
inline void CharInvs (Tensor2<Type,Dim> const & A, Type & Ia, Type & IIa, Type & IIIa)
{
    // characteristic invariants
    Type two   = static_cast<Type>(2);
    Type three = static_cast<Type>(3);
    Ia   = Tr(A);
    IIa  = (Ia*Ia - Tr(A*A))/two;
    IIIa = (Tr(A*A*A) - three*Tr(A*A)*Ia/two + Ia*Ia*Ia/two)/three;
}

/** Inverse. */
template<typename Type, int Dim>
inline void Inv (Tensor2<Type,Dim> const & A, Tensor2<Type,Dim> & Ai)
{
    // characteristic invariants
    Type Ia,IIa,IIIa;
    CharInvs (A, Ia,IIa,IIIa);

    // identity
    Tensor2<Type,Dim> I;
    I.SetKronecker();

    // inverse (should check |IIIa|>0)
    Ai = (A*A - A*Ia + I*IIa) / IIIa; // TODO: Check if transpose is necessary
}

/*************************************************************************************
 * Tensors - A C++ library to work with tensors                                      *
 * Copyright (C) 2005 Dorival de Moraes Pedroso <dorival.pedroso em gmail.com>       *
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

}; // namespace TensorsLib

#endif
