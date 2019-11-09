#pragma once

#include<GridParam.h>
class Assembler
{
public:
	Assembler(GridParam param);
	void Assemble();

private:
	GridParam p;
};

