#pragma once

#include <math.h>

#include <boost/exception_ptr.hpp> 
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include<GridParam.h>


class Solver
{
public:
	Solver(GridParam param);
	void Solve();

private:
	GridParam p;
	matrix_d truss_kl(int i);
	matrix_d truss_C(int i);
	vector_d truss_g(int i);
	void form_KK(matrix_d& KK, matrix_d kg, vector_d g);
	void form_truss_F(vector_d& F);
	vector_d LinearSolver_LU(matrix_d A, vector_d b);
};

