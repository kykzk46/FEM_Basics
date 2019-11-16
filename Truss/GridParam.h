#pragma once

#include <boost/numeric/ublas/matrix.hpp>

typedef boost::numeric::ublas::vector<double> vector_d;
typedef boost::numeric::ublas::vector<int> vector_i;
typedef boost::numeric::ublas::matrix<double> matrix_d;
typedef boost::numeric::ublas::matrix<int> matrix_i;

class GridParam
{
public:
	GridParam() : nnd(0), nel(0), nne(0), nodof(0), eldof(0), n(0)
	{}

	int nnd; // Number of nodes
	int nel; // Number of elements
	int nne; // Number of nodes per element
	int nodof; // Number of degrees of freedom per node
	matrix_d geom; // Nodes coord. (X,Y)
	matrix_i connec; // Element connectivity
	matrix_d prop; // Geometrical properties
	matrix_d nf; // Boundary conditions
	matrix_d load; // load at node
	
	int eldof; // Number of degrees of freedom per element (size of local stiffness matrix)
	int n; // Number of unknown in global stiffness matrix
};

