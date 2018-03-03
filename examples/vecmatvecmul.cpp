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
#include <string>
#include <ginac/ginac.h>

#include <tensor1.h>
#include <tensor2.h>
#include <tensor3.h>
#include <tensor4.h>
#include <operators.h>

typedef GiNaC::symbol _S;

using namespace std;
using namespace TensorsLib;

int main(int argc, char **argv)
{
    // identity and D tensor
    const size_t n = 10;
    Tensor2<GiNaC::ex,n> A, B, C;

    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n; ++j) {
            std::ostringstream oa, ob, oc;
            oa << "a" << i << j;
            ob << "b" << i << j;
            //oc << "c" << i << j;
            A[i][j] = _S(oa.str());
            B[i][j] = _S(ob.str());
            //C[i][j] = _S(oc.str());
        }
    }

    cout << "A =\n" << A << endl;
    cout << "B =\n" << B << endl;

    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n; ++j) {
            C[i][j] = 0;
            for (size_t k=0; k<n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    C.SetMaxima();
    cout << "C =\n" << C << endl;

    // end
	return 0;
}
