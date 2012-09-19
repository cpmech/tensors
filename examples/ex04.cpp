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

#include <tensors/tensor1.h>
#include <tensors/tensor2.h>
#include <tensors/tensor3.h>
#include <tensors/tensor4.h>
#include <tensors/operators.h>

using std::cout;
using std::endl;
using namespace TensorsLib;

int main(int argc, char **argv) try
{
	Tensor2<double,3> a("1 2 3  2 5 6  3 6 6");
	Tensor2<double,3> S       = a.Dev();
	Tensor2<double,3> invS    = S.Inv();       invS   .SetWid(12);
	Tensor2<double,3> SS      = S * S;         SS     .SetWid(12);
	Tensor2<double,3> devInvS = invS.Dev();    devInvS.SetWid(12);
	Tensor2<double,3> devSS   = SS.Dev();      devSS  .SetWid(12);
	Tensor2<double,3> devSS_d = devSS/S.Det(); devSS_d.SetWid(12);

	cout << "a =            \n" << a         << endl;
	cout << "S =            \n" << S         << endl;
	cout << "trace(S) =       " << S.Trace() << endl;
	cout << "det(S) =         " << S.Det()   << endl;
	cout << "inv(S) =       \n" << invS      << endl;
	cout << "S * S =        \n" << SS        << endl;
	cout << "devSS =        \n" << devSS     << endl;
	cout << "devInv(S) =    \n" << devInvS   << endl;
	cout << "devSS/det(S) = \n" << devSS_d   << endl;

	return 0;
}
catch (char const * m)
{
	cout << m << endl;
	return 1;
}
catch (...)
{
	std::cout << "Some exception (...) ocurred\n";
}

// vim:fdm=marker
