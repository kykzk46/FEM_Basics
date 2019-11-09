#pragma once

#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;
class GridParam
{
public:
	int nnd; // Number of nodes
	int nel; // Number of elements
	int nne; // Number of nodes per element
	int nodof; // Number of degrees of freedom per node
	int eldof; // Number of degrees of freedom per element
	matrix<double> geom; // Nodes coord. (X,Y)
	matrix<int> connec; // Element connectivity
	matrix<double> prop; // Geometrical properties
	matrix<double> nf; // Boundary conditions
	matrix<double> load; // load at node
	
	int n; // Number of unknown
};

