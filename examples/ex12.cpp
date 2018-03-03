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
    // input
    bool show_9D = true;
    if (argc>1) show_9D = atoi(argv[1]);

    // symbols
    GiNaC::symbol K("K");
    GiNaC::symbol G("G");

    // 3Dx3D Tensors
    Tensor2<GiNaC::ex,3> I;
    Tensor4<GiNaC::ex,3> IIsy;
    Tensor4<GiNaC::ex,3> IdyI;
    Tensor4<GiNaC::ex,3> Psd;
    Tensor4<GiNaC::ex,3> Dkg;

    // 9D Tensors in Mandel's basis
    Tensor2<GiNaC::ex,9> IIsy_m;
    Tensor2<GiNaC::ex,9> IdyI_m;
    Tensor2<GiNaC::ex,9> Psd_m;
    Tensor2<GiNaC::ex,9> Dkg_m;

    // 6D (symmetric) tensors in Mandel's basis
    Tensor2<GiNaC::ex,6> IIsy_m_sym;
    Tensor2<GiNaC::ex,6> IdyI_m_sym;
    Tensor2<GiNaC::ex,6> Psd_m_sym;
    Tensor2<GiNaC::ex,6> Dkg_m_sym;

    // identity
    I.SetKronecker();
    cout << "I =\n" << I << endl << endl;

    // isotropic tensors
    IdyI = (I & I);
    IIsy = ((I^I) + (I|I)) / 2;
    Psd  = IIsy - IdyI/3;

    // elastic stiffness
    Dkg = Psd*(2*G) + IdyI*K;

    // Mandel's basis: 9D
    IdyI.GetMandel (IdyI_m);
    IIsy.GetMandel (IIsy_m);
    Psd .GetMandel (Psd_m);
    Dkg .GetMandel (Dkg_m);

    // Mandel's basis: 6D
    IdyI.GetMandelSym (IdyI_m_sym);
    IIsy.GetMandelSym (IIsy_m_sym);
    Psd .GetMandelSym (Psd_m_sym);
    Dkg .GetMandelSym (Dkg_m_sym);

    // output
    if (show_9D)
    {
        cout << "=================================== 9D Tensors in Mandel's basis ===============================" << endl << endl;
        cout << "IdyI =\n" << IdyI_m << endl << endl;
        cout << "IIsy =\n" << IIsy_m << endl << endl;
        cout << "Psd =\n"  << Psd_m  << endl << endl;
        cout << "Dkg =\n"  << Dkg_m  << endl << endl;
    }
    cout << "=================================== 6D Tensors in Mandel's basis ===============================" << endl << endl;
    cout << "IdyI =\n" << IdyI_m_sym << endl << endl;
    cout << "IIsy =\n" << IIsy_m_sym << endl << endl;
    cout << "Psd  =\n" << Psd_m_sym  << endl << endl;
    //Dkg_m_sym.SetMaxima();
    cout << "Dkg  =\n" << Dkg_m_sym  << endl << endl;

    // end
	return 0;
}
