#include "DataReader.h"

bool DataReader::Read(std::string path)
{
	std::ifstream i(path);
	/*
	if (i.is_open())
	{
		std::string line;
  		while (std::getline(i,line))
		{
			std::cout << line << '\n';
		}
		i.close();
	}

	return true;
*/
	if (!i.is_open())
		return false;

	i >> j;

	return true;
}


void DataReader::DumpJson(std::string path)
{
	if (j == NULL)
		return;
	std::ofstream o(path);
	o << std::setw(4) << j << std::endl;
}
