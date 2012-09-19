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
#include <vector>

#include <tensors/tensor1.h>
#include <tensors/tensor2.h>
#include <tensors/tensor3.h>
#include <tensors/tensor4.h>
#include <tensors/operators.h>

using std::cout;
using std::endl;
using std::vector;
using namespace TensorsLib;

int main(int argc, char **argv) try
{
	Tensor2<double,3>           a("10 4 5  4 20 6  5 6 30");
	Tensor2<double,3>           b("-1 4 6  4 -2 5  6 5 3 ");
	vector<double>              L;
	vector< Tensor2<double,3> > P;

	a.GetEigen(L,P);

	cout << "a = \n" << a    << endl; for (size_t i=0; i<L.size(); ++i) { P[i].SetWid(10);
	cout << "L = "   << L[i] << endl;
	cout << "P = \n" << P[i] << endl; }

	cout << endl;

	b.GetEigen(L,P);

	cout << "b = \n" << b    << endl; for (size_t i=0; i<L.size(); ++i) { P[i].SetWid(10);
	cout << "L = "   << L[i] << endl;
	cout << "P = \n" << P[i] << endl; }

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
