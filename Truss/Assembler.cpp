#include "Assembler.h"


Assembler::Assembler(GridParam param)
{
	this->p = param;
}
	
void Assembler::Assemble()
{
	vector<double> KK(p.n);
	vector<double> F(p.n);

	for (int i = 0; i < p.nel; ++i)
	{
		//double* kl = truss_kl(i);
		//double* C = truss_C(i);

	}
}

matrix<double> Assembler::truss_kl(int i, int numOfUnknown)
{
	matrix<double> kl((size_t)p.n+1, (size_t)p.n+1);


	return kl;
}

