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

#include <iostream>
#include <sstream>
#include <iomanip>

#include <tensor1.h>
#include <tensor2.h>
#include <tensor3.h>
#include <tensor4.h>
#include <operators.h>

using namespace std;
using namespace TensorsLib;

int main(int nargs, char **args, char **envs)
{
	Tensor1<double,3> T1;
	Tensor2<double,3> T2;
	Tensor3<double,3> T3;
	Tensor4<double,3> T4;
	
	T1.SetWid(1);
	T2.SetWid(2);
	T3.SetWid(3);
	T4.SetWid(4);
	
	// Input/Output
	
	for (int i=0; i<3; ++i)
	{
		T1[i] = i;
		for (int j=0; j<3; ++j)
		{
			T2[i][j] = i*10 + j;
			for (int k=0; k<3; ++k)
			{
				T3[i][j][k] = i*100 + j*10 + k;
				for (int l=0; l<3; ++l)
				{
					T4[i][j][k][l] = i*1000 + j*100 + k*10 + l;
				}
			}
		}
	}

	cout << setfill('0');

	cout << "T1 = \n" << T1 << endl;
	cout << "T2 = \n" << T2 << endl;
	cout << "T3 = \n" << T3 << endl;
	cout << "T4 = \n" << T4 << endl;
	
	istringstream iss;
	
	// T1: Raw data
	iss.str("0 1 2");
	iss >> T1; // Raw data
	cout << "T1 = \n" << T1 << endl;

	// T2: Raw data
	iss.clear();
	iss.str("00 01 02  10 11 12  20 21 22");
	iss >> T2; // Raw data
	cout << "T2 = \n" << T2 << endl;
	
	// T3: Raw data
	iss.clear();
	iss.str("   0   1   2    10  11  12    20  21  22  \
			  100 101 102   110 111 112   120 121 122  \
			  200 201 202   210 211 212   220 221 222  ");
	iss >> T3; // Raw data
	cout << "T3 = \n" << T3 << endl;

	// T4: Raw data
	iss.clear();
	iss.str("   0    1    2   10   11   12   20   21   22  \
			  100  101  102  110  111  112  120  121  122  \
			  200  201  202  210  211  212  220  221  222  \
			 1000 1001 1002 1010 1011 1012 1020 1021 1022  \
			 1100 1101 1102 1110 1111 1112 1120 1121 1122  \
			 1200 1201 1202 1210 1211 1212 1220 1221 1222  \
			 2000 2001 2002 2010 2011 2012 2020 2021 2022  \
			 2100 2101 2102 2110 2111 2112 2120 2121 2122  \
			 2200 2201 2202 2210 2211 2212 2220 2221 2222 ");
	iss >> T4; // Raw data
	cout << "T4 = \n" << T4 << endl;

	// Copy constructor
	
	Tensor1<double,3> S1(T1); S1.SetWid(1);
	Tensor2<double,3> S2(T2); S2.SetWid(2);
	Tensor3<double,3> S3(T3); S3.SetWid(3);
	cout << "S1 = \n" << S1 << endl;
	cout << "S2 = \n" << S2 << endl;
	cout << "S3 = \n" << S3 << endl;

	double m=0;
	for (int i=0; i<3; ++i)
	for (int j=0; j<3; ++j)
	for (int k=0; k<3; ++k)
	for (int l=0; l<3; ++l)
	{
		T4[i][j][k][l] = m;
		m++;
	}
	T4.SetWid(2);
	cout << "T4 = \n" << T4 << endl;
		
	Tensor4<double,3> S4(T4);
	S4.SetWid(2);
	cout << "S4 = \n" << S4 << endl;
	
	
	cout << setfill(' ');

	return 0;
}
