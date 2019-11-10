#pragma once

#include <math.h>

#include <boost/exception_ptr.hpp> 
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include<GridParam.h>

using namespace boost::numeric::ublas;

class Assembler
{
public:
	Assembler(GridParam param);
	void Assemble();

private:
	GridParam p;
	int numUnk;
	matrix<double> truss_kl(int i);
	matrix<double> truss_C(int i);
	vector<double> truss_g(int i);
	void form_KK(matrix<double>& KK, matrix<double> kg, vector<double> g);
	void form_truss_F(vector<double>& F);
};

