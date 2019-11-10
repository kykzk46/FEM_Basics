#include "Assembler.h"


Assembler::Assembler(GridParam param)
{
	this->p = param;
	this->numUnk = p.n + 1;
}
	
void Assembler::Assemble()
{
	matrix<double> KK(this->numUnk, this->numUnk);
	vector<double> F(this->numUnk);

	for (int i = 0; i < p.nel; ++i)
	{
		matrix<double> kl = truss_kl(i); //local k
		matrix<double> C = truss_C(i); 
		matrix<double> C_t = trans(C);
		matrix<double> kg = prod(C, kl, C_t);
		vector<double> g =truss_g(i);

		// Assemble global stiffness matrix
		form_KK(KK, kg, g);
	}
}

matrix<double> Assembler::truss_kl(int elemId)
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
	matrix<double> kl(this->numUnk, this->numUnk);
	double temp = E * A / L;
 	kl(0, 0) = temp;
 	kl(0, 2) = -temp;
 	kl(2, 0) = -temp;
 	kl(2, 2) = temp;

	return kl;
}

matrix<double> Assembler::truss_C(int elemId)
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
	matrix<double> C(this->numUnk, this->numUnk);
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
vector<double> Assembler::truss_g(int elemId)
{
	// Retrive node id from element i
	int node_1 = p.connec(elemId, 0);
	int node_2 = p.connec(elemId, 1);

	vector<double> g(4);
	g(0) = p.nf(node_1, 0);
	g(1) = p.nf(node_1, 1);
	g(2) = p.nf(node_1, 2);
	g(3) = p.nf(node_1, 3);

	return g;
}

void Assembler::form_KK(matrix<double>& KK, matrix<double> kg, vector<double> g)
{
	for (int i = 0; i < p.eldof; ++i)
	{
		if (g(i) != 0)
		{
			for (int j = 0; j < p.eldof; ++j)
			{
				if (g(j) != 0)
					KK(g(i), g(j)) = KK(g(i), g(j)) + kg(i, j);
			}
		}
	}

}

void Assembler::form_truss_F(vector<double>& F)
{
	for (int i = 0; i < p.nnd; ++i)
	{
		for (int j = 0; j < p.nodof; ++j)
		{
			if (p.nf(i, j) != 0)
			{
				F(p.nf(i, j)) = p.load(i, j);
			}
		}
	}
}






















