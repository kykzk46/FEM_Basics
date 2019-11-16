#include "Solver.h"


Solver::Solver(GridParam param)
{
	this->p = param;
}
	
void Solver::Solve()
{
	// Global stiffness matrix and force vector
	matrix_d KK(p.n, p.n, .0);
	vector_d F(p.n, .0);

	for (int i = 0; i < p.nel; ++i)
	{
		matrix_d kl = truss_kl(i); //local k
		matrix_d C = truss_C(i); // local to global transformation matrix
		matrix_d kg = prod(C, matrix_d(prod(kl, trans(C)))); // global k = C * k * trans(C)
		
		vector_i g = truss_g(i); // Steering vector

		form_KK(KK, kg, g); // Assemble global stiffness matrix
		
		std::cout << "Elem id:" << i << std::endl;
		std::cout << kl << std::endl;
		std::cout << C << std::endl;
		std::cout << kg << std::endl;
		std::cout << g << std::endl;
		std::cout << KK << std::endl;
	}

	// Form global force vector
	form_truss_F(F);
	std::cout << F << std::endl;
 
	vector_d delta = LinearSolver_LU(KK, F);
	std::cout << delta << std::endl;

}

matrix_d Solver::truss_kl(int elemId)
{
	// Retrive node id from element i
	int node_1 = p.connec(elemId, 0);
	int node_2 = p.connec(elemId, 1);

	// Retrive  x, y coordinates of nodes 1 and 2
	double x1 = p.geom(node_1, 0);
	double y1 = p.geom(node_1, 1);
	double x2 = p.geom(node_2, 0);
	double y2 = p.geom(node_2, 1);

	// Evaluate length of element i
	double L = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	// Retrive material properties
	double E = p.prop(elemId, 0);
	double A = p.prop(elemId, 1);

	// Calculate element stiffness matrix in local coord.
	matrix_d kl(p.eldof, p.eldof, .0);
	double temp = E * A / L;
 	kl(0, 0) = temp;
 	kl(0, 2) = -temp;
 	kl(2, 0) = -temp;
 	kl(2, 2) = temp;

	return kl;
}

matrix_d Solver::truss_C(int elemId)
{
	// Retrive node id from element i
	int node_1 = p.connec(elemId, 0);
	int node_2 = p.connec(elemId, 1);

	// Retrive  x, y coordinates of nodes 1 and 2
	double x1 = p.geom(node_1, 0);
	double y1 = p.geom(node_1, 1);
	double x2 = p.geom(node_2, 0);
	double y2 = p.geom(node_2, 1);

	// Evaluate the angle that the member makes with the global coord.
	double theta;
	if ((x2 - x1) == 0)
	{
		if (y2 > y1)
			theta = 2 * atan(1);
		else
			theta = -2 * atan(1);
	}
	else
	{
		theta = atan2((y2 - y1), (x2 - x1));
	}

	// Construct the transformation matrix
	matrix_d C(p.eldof, p.eldof, .0);
	C(0, 0) = cos(theta);
	C(0, 1) = -sin(theta);
	C(1, 0) = sin(theta);
	C(1, 1) = cos(theta);
	C(2, 2) = cos(theta);
	C(2, 3) = -sin(theta);
	C(3, 2) = sin(theta);
	C(3, 3) = cos(theta);

	return C;
}

// Form steering vector
vector_d Solver::truss_g(int elemId)
{
	// Retrive node id from element i
	int node_1 = p.connec(elemId, 0);
	int node_2 = p.connec(elemId, 1);

	vector_d g(4, .0);
	g(0) = p.nf(node_1, 0);
	g(1) = p.nf(node_1, 1);
	g(2) = p.nf(node_2, 0);
	g(3) = p.nf(node_2, 1);

	return g;
}

void Solver::form_KK(matrix_d& KK, matrix_d kg, vector_d g)
{
	for (int i = 0; i < p.eldof; ++i)
	{
		if (g(i) != 0)
		{
			for (int j = 0; j < p.eldof; ++j)
			{
				if (g(j) != 0)
				{
					int rowIdx = g(i) - 1;
					int colIdx = g(j) - 1;
					KK(rowIdx, colIdx) = KK(rowIdx, colIdx) + kg(i, j);
				}
			}
		}
	}

}

void Solver::form_truss_F(vector_d& F)
{
	for (size_t i = 0; i < p.nnd; ++i)
	{
		for (size_t j = 0; j < p.nodof; ++j)
		{
			if (p.nf(i, j) != 0)
			{
				size_t idx = p.nf(i, j) - 1;
				F(idx) = p.load(i, j);
			}
		}
	}
}

// Solve Ax = b
vector_d Solver::LinearSolver_LU(matrix_d A, vector_d b)
{
	using namespace boost::numeric::ublas;

	lu_factorize(A);

	// Solve Ax = b and write result to b
	lu_substitute<const matrix_d, vector_d>(A, b);

	return vector_d (b);
}



















