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

#include <tensors/tensor1.h>
#include <tensors/tensor2.h>
#include <tensors/tensor3.h>
#include <tensors/tensor4.h>
#include <tensors/operators.h>

typedef GiNaC::symbol _S;

using namespace std;
using namespace TensorsLib;

int main()
{
	{
		Tensor2<GiNaC::ex,3> A;
		Tensor2<GiNaC::ex,3> B;
		Tensor2<GiNaC::ex,3> I;    I.SetKronecker();
		Tensor4<GiNaC::ex,3> T;
		Tensor2<GiNaC::ex,9> Tm;   Tm.SetMaxima();
		Tensor2<GiNaC::ex,6> TmSy; TmSy.SetMaxima();
		Tensor4<GiNaC::ex,3> Psd;  Psd.SetSymDev();

		A = _S("a0"), _S("a3"), _S("a5"),
		    _S("a3"), _S("a1"), _S("a4"),
		    _S("a5"), _S("a4"), _S("a2");
		B = _S("b0"), _S("b3"), _S("b5"),
		    _S("b3"), _S("b1"), _S("b4"),
		    _S("b5"), _S("b4"), _S("b2");

		T = ((A ^ B) + (B ^ A)) % Psd; // symmetric
		T.GetMandel    (Tm);
		T.GetMandelSym (TmSy);

		cout << "A = \n" << A << endl;
		cout << "B = \n" << B << endl;
		cout << "I = \n" << I << endl;
		cout << "Tm:" << Tm << endl;
		cout << "TmSy:" << TmSy << endl;
	}
	cout << endl << endl;
	{
		Tensor2<double,3> A;
		Tensor2<double,3> B;
		Tensor4<double,3> T;
		Tensor2<double,9> Tm;   Tm.SetWid(10);
		Tensor2<double,6> TmSy; TmSy.SetWid(10);
		Tensor4<double,3> Psd;  Psd.SetSymDev();

		A =  1,  7,  9,
		     7,  2,  8,
		     9,  8,  3;
		B =  4, 10, 12,
		    10,  5, 11,
		    12, 11,  6;

		T = ((A ^ B) + (B ^ A)) % Psd; // symmetric
		T.GetMandel    (Tm);
		T.GetMandelSym (TmSy);

		cout << "A = \n"    << A    << endl;
		cout << "B = \n"    << B    << endl;
		cout << "Tm = \n"   << Tm   << endl;
		cout << "TmSy = \n" << TmSy << endl;
	}

	return 0;
}
