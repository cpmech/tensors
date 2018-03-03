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

#include <tensor1.h>
#include <tensor2.h>
#include <tensor3.h>
#include <tensor4.h>
#include <operators.h>

using namespace std;
using namespace TensorsLib;

int main()
{

	// ----------------------------------- Tensor2
	
	// Kronecker
	Tensor2<double,4> T2; T2.SetWid(1);
	T2.SetKronecker();
	cout << "T2 = \n" << T2 << endl;
	
	T2.SetWid(2);
	istringstream iss;
	iss.str("0 1 2 3  10 11 12 13  20 21 22 23  30 31 32 33");
	iss >> T2;
	cout << "T2 = \n" << T2 << endl;

	// Transpose
	Tensor2<double,4> T2t; T2t.SetWid(2);
	T2.GetTranspose(T2t);
	cout << "T2transpose = \n" << T2t << endl;
	
	// Symmetric
	Tensor2<double,4> T2symm; T2symm.SetWid(6);
	T2.GetSymmetric(T2symm);
	cout << "T2symmetric = \n" << T2symm << endl;
	
	// SkewSymmetric
	Tensor2<double,4> T2skww; T2skww.SetWid(6);
	T2.GetSkewSymmetric(T2skww);
	cout << "T2skew = \n" << T2skww << endl;

	// Check
	Tensor2<double,4> T2tmp; T2tmp.SetWid(6);
	T2tmp = T2symm + T2skww;
	cout << "T2sym + T2skw = \n" << T2tmp << endl;
	
	
	// ----------------------------------- Tensor3
	
	// Permutation
	Tensor3<double,3> T3tmp; T3tmp.SetWid(3);
	for (int i=0; i<3; ++i)
	for (int j=0; j<3; ++j)
	for (int k=0; k<3; ++k)
		T3tmp[i][j][k] = 100*i + 10*j + k;
	cout << setfill('0');
	cout << "T3tmp = \n" << T3tmp << endl;
	cout << setfill(' ');
	Tensor3<double,3> EE; EE.SetWid(3);
	EE.SetPermutation();
	cout << "Permutation = \n" << EE << endl;

	// ----------------------------------- Tensor4

	// General Isotropic
	Tensor4<double,3> T4tmp; T4tmp.SetWid(4);
	for (int i=0; i<3; ++i)
	for (int j=0; j<3; ++j)
	for (int k=0; k<3; ++k)
	for (int l=0; l<3; ++l)
		T4tmp[i][j][k][l] = 1000*i + 100*j + 10*k + l;
	cout << setfill('0');
	cout << "T4tmp = \n" << T4tmp << endl;
	cout << setfill(' ');

	Tensor4<double,3> T4geiso; T4geiso.SetWid(6);
	Tensor2<double,9> T2geiso; T2geiso.SetWid(6);
	T4geiso.SetGeneralIsotropic(2,4,6);
	cout << "T4geiso = \n" << fixed << setprecision(3) << T4geiso << endl;
	T4geiso.GetMandel(T2geiso);
	cout << "T2geiso = \n" << T2geiso << endl;

	// Isotropic
	Tensor4<double,3> T4iso; T4iso.SetWid(6);
	Tensor2<double,9> T2iso; T2iso.SetWid(6);
	T4iso.SetIso();
	cout << "T4iso = \n" << T4iso << endl;
	T4iso.GetMandel(T2iso);
	cout << "T2iso = \n" << T2iso << endl;
	
	// Symmetric
	Tensor4<double,3> T4sym; T4sym.SetWid(6);
	Tensor2<double,9> T2sym; T2sym.SetWid(6);
	T4sym.SetSym();
	cout << "T4sym = \n" << T4sym << endl;
	T4sym.GetMandel(T2sym);
	cout << "T2sym = \n" << T2sym << endl;
	
	// SymmetricDeviatoric
	Tensor4<double,3> T4symdev; T4symdev.SetWid(6);
	Tensor2<double,9> T2symdev; T2symdev.SetWid(6);
	T4symdev.SetSymDev();
	cout << "T4symdev = \n" << T4symdev << endl;
	T4symdev.GetMandel(T2symdev);
	cout << "T2symdev = \n" << T2symdev << endl;
	
	// Skew-symmetric
	Tensor4<double,3> T4skw; T4skw.SetWid(6);
	Tensor2<double,9> T2skw; T2skw.SetWid(6);
	T4skw.SetSkew();
	cout << "T4skw = \n" << T4skw << endl;
	T4skw.GetMandel(T2skw);
	cout << "T2skw = \n" << T2skw << endl;
	
	// Check
	// non-Symmetric
	Tensor2<double,3> A; A.SetWid(4);
	Tensor2<double,3> B; B.SetWid(4);
	iss.clear();
	iss.str("0 1 2  10 11 12  20 21 22");
	iss >> A;
	cout << "A = \n" << setprecision(0) << A << endl;
	B = T4geiso % A;
	cout << "T4geiso % A = \n" << B << endl;
	B = T4iso % A;
	cout << "T4iso % A = \n" << B << endl;
	B = T4symdev % A;
	cout << "T4symdev % A = \n" << B << endl;
	B = T4sym % A;
	cout << "T4sym % A = \n" << B << endl;
	B = T4skw % A;
	cout << "T4skw % A = \n" << B << endl;
	
	// Symmetric
	iss.clear();
	iss.str("0 1 2  1 11 12  2 12 22");
	iss >> A;
	cout << "A = \n" << A << endl;
	B = T4geiso % A;
	cout << "T4geiso % A = \n" << B << endl;
	B = T4iso % A;
	cout << "T4iso % A = \n" << B << endl;
	B = T4symdev % A;
	cout << "T4symdev % A = \n" << B << endl;
	B = T4sym % A;
	cout << "T4sym % A = \n" << B << endl;
	B = T4skw % A;
	cout << "T4skw % A = \n" << B << endl;

	return 0;
}
