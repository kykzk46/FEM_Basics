// Truss.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <DataReader.h>

int main()
{
    std::cout << "Read .json" << std::endl;
	DataReader dr;
	dr.Read("Input/truss_1_data.json");
	dr.DumpJson("Output/test.json");

 }

