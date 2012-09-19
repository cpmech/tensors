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

#include <tensors/tensor1.h>
#include <tensors/tensor2.h>
#include <tensors/tensor3.h>
#include <tensors/tensor4.h>
#include <tensors/operators.h>

typedef GiNaC::symbol _S;

using namespace std;
using namespace TensorsLib;

int main(int argc, char **argv)
{
    // input arguments
    bool is2d = false;
    if (argc>1) is2d = atoi(argv[1]);

    // identity and D tensor
    Tensor2<GiNaC::ex,3> I;
    Tensor4<GiNaC::ex,3> D;
    I.SetKronecker();

    // show D using Mandel components?
    bool man = true;

    // symmetric 4th order tensor
	for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
    for (int k=0; k<3; ++k) {
    for (int l=0; l<3; ++l) {
        ostringstream oss;
        oss << "D";
        if (man) {
            int I = Tensor4ToMandel_i[i][j][k][l];
            int J = Tensor4ToMandel_j[i][j][k][l];
            oss << I << J;
            //if (I<J) { oss << I << J; } else { oss << J << I; } // <<< D may be non-symmetric
            std::string coef;
            if ((i==j && k!=l) || (k==l && i!=j)) { coef = "/sqrt(2)"; }
            if (i!=j && k!=l) { coef = "/2"; }
            oss << coef;
        } else {
            if (i<j) { oss << i << j; } else { oss << j << i; }
            if (k<l) { oss << k << l; } else { oss << l << k; }
        }
        D[i][j][k][l] = _S(oss.str().c_str());

        if (is2d) {
            if ((i==0 && j==2) || (i==2 && j==0)) { D[i][j][k][l] = 0; }
            if ((i==1 && j==2) || (i==2 && j==1)) { D[i][j][k][l] = 0; }
            if ((k==0 && l==2) || (k==2 && l==0)) { D[i][j][k][l] = 0; }
            if ((k==1 && l==2) || (k==2 && l==1)) { D[i][j][k][l] = 0; }
        }
    } } } }

    // D(tensor) and D(mandel)
    Tensor2<GiNaC::ex,9> Dt;
    Tensor2<GiNaC::ex,9> Dm;
    Dt.SetMaxima();
    Dm.SetMaxima();
    D.GetTensor2(Dt);
    D.GetMandel(Dm);
    cout << "\nDt:" << Dt << endl;
    cout << "\nDm:" << Dm << endl;

    // Gm = dSmdx
    Tensor1<GiNaC::ex,3> Gm, Gn;
    if (is2d) {
        Gm = _S("Gm0"), _S("Gm1"), _S("0");
        Gn = _S("Gn0"), _S("Gn1"), _S("0");
    } else {
        Gm = _S("Gm0"), _S("Gm1"), _S("Gm2");
        Gn = _S("Gn0"), _S("Gn1"), _S("Gn2");
    }

    // components of stiffness matrix => maxima
	for (int a=0; a<3; ++a) {
        for (int b=0; b<3; ++b) {
            GiNaC::ex res;
            for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
            for (int k=0; k<3; ++k) {
                res += D[a][k][i][j] * Gm[k] * (I[i][b]*Gn[j] + I[j][b]*Gn[i]) / 2;
            } } }
            cout << "Kmn" << a << b << ":" << res << ", ratsimp;" << endl;
        }
    }

    // generate fortran file from maxima
    if (is2d) {
        cout << "\nload(f90);\nwith_stdout(\"smat2d.f90\",";
    } else {
        cout << "\nload(f90);\nwith_stdout(\"smat3d.f90\",";
    }
	for (int a=0; a<3; ++a) {
        for (int b=0; b<3; ++b) {
            cout << "f90('Kmn" << a << b << "=Kmn" << a << b << ")";
            if (a==2 && b==2) {
                // last one
            } else {
                cout << ",";
            }
        }
    }
    cout << ");\n";

    // end
	return 0;
}
