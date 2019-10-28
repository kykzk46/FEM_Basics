#pragma once

#include<string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Grid
{
public:
	int nnd; // Number of nodes
	int nel; // Number of elements
	int nne; // Number of nodes per element
	int nodof; // Number of degrees of freedom per node
	int eldof; // Number of degrees of freedom per element
	double* geom; // Nodes coord. (X,Y)
	int* connec; // Element connectivity
	double* prop; // Geometrical properties
	double* nf; // Boundary conditions
	double* load; // load at node

	bool ReadFromJson(json& j);
};

