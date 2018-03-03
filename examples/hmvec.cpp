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
    // input arguments
    bool is2d = false;
    if (argc>1) is2d = atoi(argv[1]);

    // ndim
    int ndim = (is2d ? 2 : 3);

    // Gm = dSmdx
    // vg = [0,0,-1] or [0,-1,0]
    Tensor1<GiNaC::ex,3> Gm, Gn, vg;
    if (ndim==2) {
        Gm = _S("Gm0"), _S("Gm1"), _S("0");
        Gn = _S("Gn0"), _S("Gn1"), _S("0");
        vg = 0, -1, 0;
    } else {
        Gm = _S("Gm0"), _S("Gm1"), _S("Gm2");
        Gn = _S("Gn0"), _S("Gn1"), _S("Gn2");
        vg = 0, 0, -1;
    }

    // kap
    Tensor2<GiNaC::ex,3> kap;
    for (size_t i=0; i<3; ++i) {
        for (size_t j=0; j<3; ++j) {
            std::ostringstream oss;
            oss << "k" << i << j;
            kap[i][j] = _S(oss.str());
        }
    }

    // GmKvg
    GiNaC::ex res;
    for (int i=0; i<ndim; ++i) {
        for (int j=0; j<ndim; ++j) {
            res += Gm[i] * kap[i][j] * vg[j];
        }
    }
    cout << "hm:" << res << ", ratsimp;\n";

    // f90
    if (ndim==2) {
        cout << "\nload(f90);\nwith_stdout(\"hmvec2d.f90\",";
    } else {
        cout << "\nload(f90);\nwith_stdout(\"hmvec3d.f90\",";
    }
    cout << "f90('hm=hm)";
    cout << ");\n";

    // end
	return 0;
}
