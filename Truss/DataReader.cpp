#include "DataReader.h"

bool DataReader::Read(std::string path)
{
	std::ifstream i(path);
	if (!i.is_open())
		return false;

	i >> j;

	JsonImporter importer;
	this->gridParam = importer.ReadFromJson(j);
	
	// debug
	importer.PrintParam();

	return importer.isReadSuccess;
}


void DataReader::DumpJson(std::string path)
{
	if (j == NULL)
		return;
	std::ofstream o(path);
	o << std::setw(4) << j << std::endl;
}

GridParam DataReader::GetFEMGrid()
{
	return this->gridParam;
}
