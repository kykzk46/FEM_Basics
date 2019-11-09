#pragma once

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
	matrix<double> truss_kl(int i, int numOfUnknown);
};

