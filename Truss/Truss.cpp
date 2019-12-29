// Truss.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <DataReader.h>
#include <Solver.h>

int main()
{
    std::cout << "Start reading json file" << std::endl;
	DataReader dr;

	// Input file for problem 1
	// std::string path = "Input/truss_1_data.json";
	// Input file for problem 2
	std::string path = "Input/truss_2_data.json";
	
	// Debug
	//dr.DumpJson(path);

	dr.Read(path);
	GridParam grid_param = dr.GetFEMGrid();

	Solver s(grid_param);
	s.Solve();
 }

