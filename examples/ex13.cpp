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
    // 3Dx3D Tensors
    Tensor2<GiNaC::ex,3> s, l, lT, w, res;

    // 9D Tensors in Mandel's basis
    Tensor1<GiNaC::ex,9> s_m, l_m, w_m, res_m;

    s    .SetMaxima();
    l    .SetMaxima();
    w    .SetMaxima();
    res  .SetMaxima();
    s_m  .SetMaxima();
    l_m  .SetMaxima();
    w_m  .SetMaxima();
    res_m.SetMaxima();

    s = _S("sxx"), _S("sxy"), _S("szx"),
        _S("sxy"), _S("syy"), _S("syz"),
        _S("szx"), _S("syz"), _S("szz");

    //l = _S("lxx"), _S("lxy"), _S("lxz"),
        //_S("lyx"), _S("lyy"), _S("lyz"),
        //_S("lzx"), _S("lzy"), _S("lzz");

    l = _S("T[1,1]"), _S("T[1,2]"), _S("T[1,3]"),
        _S("T[2,1]"), _S("T[2,2]"), _S("T[2,3]"),
        _S("T[3,1]"), _S("T[3,2]"), _S("T[3,3]");

    s.GetMandel(s_m);
    l.GetMandel(l_m);
    cout << "s:"   << s   << endl;
    cout << "s_m:" << s_m << endl;
    cout << "l:"   << l   << endl;
    cout << "l_m:" << l_m << endl;

    s = _S("S(0)"),         _S("S(3)/sqrt(2)"), _S("S(5)/sqrt(2)"),
        _S("S(3)/sqrt(2)"),         _S("S(1)"), _S("S(4)/sqrt(2)"),
        _S("S(5)/sqrt(2)"), _S("S(4)/sqrt(2)"), _S("S(2)");

    l = _S("L(0)"), _S("L(3)"), _S("L(5)"),
        _S("L(6)"), _S("L(1)"), _S("L(4)"),
        _S("L(8)"), _S("L(7)"), _S("L(2)");

    l.GetTranspose(lT);
    w   = (l-lT)*GiNaC::symbol("(1/2)");
    res = w*s - s*w;

    s  .GetMandel (s_m);
    l  .GetMandel (l_m);
    w  .GetMandel (w_m);
    res.GetMandel (res_m);

    cout << "s:"             << s     << endl;
    cout << "l:"             << l     << endl;
    cout << "w:"             << w     << endl;
    cout << "s_m:"           << s_m   << endl;
    cout << "l_m:"           << l_m   << endl;
    cout << "w_m:"           << w_m   << endl;
    cout << "ws_minus_sw:"   << res   << endl;
    cout << "ws_minus_sw_m:" << res_m << endl;

    // end
	return 0;
}
