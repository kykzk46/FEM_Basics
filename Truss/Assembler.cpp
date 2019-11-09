#include "Assembler.h"


Assembler::Assembler(GridParam param)
{
	this->p = param;
}
	
void Assembler::Assemble()
{
	double* KK = new double[p.n];
	double* ptr = new double  [p.n];

	for (int i = 0; i < p.nel; ++i)
	{
		//double* kl = truss_kl(i);
		//double* C = truss_C(i);

	}
}

