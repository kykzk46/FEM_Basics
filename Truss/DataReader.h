#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <nlohmann/json.hpp>
#include <Grid.h>	

using json = nlohmann::json;

class DataReader
{
public:
	bool Read(std::string path);
	void DumpJson(std::string path);
	Grid GetFEMGrid();
private: 
	json j;
	Grid g;
};

