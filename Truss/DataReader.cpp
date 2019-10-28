#include "DataReader.h"

bool DataReader::Read(std::string path)
{
	std::ifstream i(path);
	if (!i.is_open())
		return false;

	i >> j;

	bool rst = this->g.ReadFromJson(j);

	return rst;
}


void DataReader::DumpJson(std::string path)
{
	if (j == NULL)
		return;
	std::ofstream o(path);
	o << std::setw(4) << j << std::endl;
}

Grid DataReader::GetFEMGrid()
{
	return this->g;
}
