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
#include <iomanip>
#include <sstream>
#include <ginac/ginac.h>

#include <tensor1.h>
#include <tensor2.h>
#include <tensor3.h>
#include <tensor4.h>
#include <operators.h>

using namespace std;
using namespace TensorsLib;

int main()
{
	Tensor2<GiNaC::ex,3> A;
	Tensor2<GiNaC::ex,3> B;
	Tensor2<GiNaC::ex,3> I;
	Tensor4<GiNaC::ex,3> T;
	Tensor2<GiNaC::ex,9> Tm;
	Tensor4<GiNaC::ex,3> Psd;
	Tensor4<GiNaC::ex,3> W;
	Tensor2<GiNaC::ex,9> Wm;
	I.SetKronecker();
	//Tm.SetMaxima();
	Psd.SetSymDev();
	for (int i=0; i<3; ++i)
	for (int j=0; j<3; ++j)
	{
		std::ostringstream sa; sa<<"a"<<Tensor2ToMandel_i[i][j];
		std::ostringstream sb; sb<<"b"<<Tensor2ToMandel_i[i][j];
		GiNaC::symbol sya(sa.str());
		GiNaC::symbol syb(sb.str());
		A[i][j] = sya;
		B[i][j] = syb;
	}
	//T = (A ^ B) + (A | B); // not symmetric
	//T = (A ^ B) + (B | A); // not symmetric
	//T = (A ^ A) + (A | A); // symmetric
	//T = (I ^ A) + (I | A); // not symmetric
	//T = (I ^ A) + (A | I); // not symmetric
	//T = (A ^ I) + (I | A); // not symmetric
	T = (I ^ A) + (A ^ I); // not symmetric
	W = T % Psd;           // symmetric ?
	T.GetMandel (Tm);
	W.GetMandel (Wm);
	cout << "A = \n" << A << endl;
	cout << "B = \n" << B << endl;
	cout << "I = \n" << I << endl;
	cout << "T = \n" << T << endl;
	cout << "W = \n" << W << endl;
	cout << "Tm = \n" << Tm << endl;
	cout << "Wm = \n" << Wm << endl;

	return 0;
}
