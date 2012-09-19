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

#include <tensors/tensor1.h>
#include <tensors/tensor2.h>
#include <tensors/tensor3.h>
#include <tensors/tensor4.h>
#include <tensors/operators.h>

using namespace std;
using namespace TensorsLib;

int main(int argc, char **argv) {
    Tensor1<double,3> T1;
    Tensor2<double,3> T2;
    Tensor3<double,3> T3;
    Tensor4<double,3> T4;
    for (int i=0; i < 3; ++i) {
        T1[i] = i+1;
        for (int j=0; j < 3; ++j) {
            T2[i][j] = (i+1)*10 + j+1;
            for (int k=0; k < 3; ++k) {
                T3[i][j][k] = (i+1)*100 + (j+1)*10 + k+1;
                for (int l=0; l < 3; ++l) {
                    T4[i][j][k][l] = (i+1)*1000 + (j+1)*100 + (k+1)*10 + l+1;
                }
            }
        }
    }
	cout << "T1 = \n" << T1 << "\n\n";
	cout << "T2 = \n" << T2 << "\n\n";
	cout << "T3 = \n" << T3 << "\n\n";
	cout << "T4 = \n" << T4 << "\n";
    return 0;
}
