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
	double Young   = 10;
	double Poisson = 0.20;
	Tensor2<double,3> s;     // Stress
	Tensor2<double,3> e;     // Strain
	Tensor2<double,3> I;     // Second order identity
	Tensor4<double,3> IIsym; // Fourth order symmetric identity
	Tensor4<double,3> C;     // Compliance
	Tensor4<double,3> D;     // Stiffness

	// Stress
	s[0][0]=10; s[0][1]=4;  s[0][2]=6;
	s[1][0]=4;  s[1][1]=20; s[1][2]=5;
	s[2][0]=6;  s[2][1]=5;  s[2][2]=30;

	// Indentities
	I.SetKronecker();
	IIsym = ((I ^ I) + (I | I)) * 0.5;

	// Compliance and Stiffness
	C = IIsym*((1.0+Poisson)/Young) - (I & I)*(Poisson/Young);
	D = IIsym*(Young/(1.0+Poisson)) + (I & I)*(Poisson*Young/ ((1.0+Poisson)*(1.0-2.0*Poisson)));

	// Strain
	e = C % s;

	// Output
	//cout << "s          = \n" << s               << endl;
	//cout << "e          = \n" << e               << endl;
	//cout << "s - D \% e = \n" << s - (D % e)     << endl; // Must be zero
	//cout << "IIsym      = \n" << IIsym           << endl;
	//cout << "C          = \n" << C               << endl;
	//cout << "D          = \n" << D               << endl;
	//cout << "D \% C     = \n" << (D % C) - IIsym << endl; // Must be zero
	
	Tensor2<double,9> Dt; Dt.SetWid(8);
	D.GetTensor2(Dt);
	cout << "D =\n" << Dt << endl;

	return 0;
}
catch (char const * m) // {{{
{
	cout << m << endl;
	return 1;
}
catch (...)
{
	std::cout << "Some exception (...) ocurred\n";
} // }}}

// vim:fdm=marker
