// Truss.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <DataReader.h>
#include <Assembler.h>

int main()
{
    std::cout << "Start reading json file" << std::endl;
	DataReader dr;

	std::string path = "Input/truss_1_data.json";
	
	// Debug
	//dr.DumpJson(path);

	dr.Read(path);
	GridParam grid_param = dr.GetFEMGrid();

	// Note: asm is an occupied name
	Assembler fem_asm(grid_param);
	fem_asm.Assemble();
	

 }

