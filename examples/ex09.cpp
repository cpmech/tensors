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

using namespace std;
using namespace TensorsLib;

int main()
{
	// 2nd order
	Tensor2<GiNaC::ex,3> A; A.SetWid(2);
	Tensor2<GiNaC::ex,3> B; B.SetWid(2);
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
	//A.SetKronecker();
	//B.SetKronecker();
	cout << "A = \n" << A << endl;
	cout << "B = \n" << B << endl;
	cout << endl;

	Tensor4<GiNaC::ex,3> T;
	Tensor4<GiNaC::ex,3> W;
	Tensor2<GiNaC::ex,9> Tm;  Tm.SetWid(13);
	Tensor2<GiNaC::ex,9> Wm;  Wm.SetWid(13);
	T = (A ^ B) + (B | A);
	W = (A ^ B) + (A | B);
	T.GetMandel(Tm);
	W.GetMandel(Wm);
	cout << "T  = \n" << T << endl;
	cout << "Tm = \n" << Tm << endl;
	cout << "W  = \n" << T << endl;
	cout << "Wm = \n" << Tm << endl;
	cout << "T-W  = \n" << T-W << endl;
	cout << endl;


	return 0;
}
