// Truss.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <DataReader.h>

int main()
{
    std::cout << "Start reading json file" << std::endl;
	DataReader dr;

	std::string path = "Input/truss_1_data.json";
	
	// Debug
	//dr.DumpJson(path);

	dr.Read(path);
	GridParam grid = dr.GetFEMGrid();


 }

