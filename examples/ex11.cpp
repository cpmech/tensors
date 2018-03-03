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

typedef GiNaC::symbol _S;

using namespace std;
using namespace TensorsLib;

int main(int argc, char **argv)
{
    int test = 1;
    if (argc>1) test = atoi(argv[1]);

    if (test==1)
    {
        Tensor2<GiNaC::ex,3> invA;
        Tensor4<GiNaC::ex,3> dInvA_dA;
        Tensor2<GiNaC::ex,9> dInvA_dA_m;  dInvA_dA_m.SetMaxima();
        invA =  _S("Ai0"),         _S("Ai3")/_S("s"), _S("Ai5")/_S("s"),
                _S("Ai3")/_S("s"), _S("Ai1"),         _S("Ai4")/_S("s"),
                _S("Ai5")/_S("s"), _S("Ai4")/_S("s"), _S("Ai2");
        dInvA_dA = ((invA^invA) + (invA|invA)) * (-0.5);
        dInvA_dA.GetMandel (dInvA_dA_m);
        cout << "invA =\n"     << invA       << endl << endl;
        cout << "dInvA_dA =\n" << dInvA_dA_m << endl << endl;
    }
    else if (test==2)
    {
        Tensor2<double,3> A;
        Tensor2<double,3> invA;
        Tensor4<double,3> dInvA_dA;
        Tensor2<double,9> dInvA_dA_m;
        A =  -90.0,   1.0,   1.5,
               1.0, -20.0,   2.0,
               1.5,   2.0, -20.0;
        Inv (A, invA);
        dInvA_dA = ((invA^invA) + (invA|invA)) * (-0.5);
        dInvA_dA.GetMandel (dInvA_dA_m);
        cout << "A =\n"        << A          << endl << endl;
        cout << "invA =\n"     << invA       << endl << endl;
        cout << "A*invA =\n"   << A*invA     << endl << endl;
        cout << "dInvA_dA =\n" << dInvA_dA_m << endl << endl;
    }
    else cout << "test == " << test << " is not available" << endl;

	return 0;
}
