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
#include <ginac/ginac.h>

#include <tensor1.h>
#include <tensor2.h>
#include <tensor3.h>
#include <tensor4.h>
#include <operators.h>

using namespace std;
using namespace TensorsLib;

int main(int argc, char **argv) {
    Tensor4<GiNaC::ex,3> T4;
    for (int i=0; i < 3; ++i) {
        for (int j=0; j < 3; ++j) {
            for (int k=0; k < 3; ++k) {
                for (int l=0; l < 3; ++l) {
                    std::ostringstream oss;
                    oss << "D" << (i+1)*1000 + (j+1)*100 + (k+1)*10 + l+1;
                    T4[i][j][k][l] = GiNaC::symbol(oss.str().c_str());
                }
            }
        }
    }
    Tensor2<GiNaC::ex,9> T4m;
    T4m.SetMaxima();
    T4.GetMandel(T4m);
	cout << "T4m : " << T4m << "\n";
    cout << "load(f90);\nwith_stdout(\"doc02.f90\",f90('T4=T4m));\n";
    return 0;
}
