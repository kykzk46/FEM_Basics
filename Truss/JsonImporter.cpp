#include "JsonImporter.h"

bool JsonImporter::ReadFromJson(json& j)
{
	try
	{
		j.at("nnd").get_to(gridParam.nnd); // Num. of nodes
		j.at("nel").get_to(gridParam.nel); // Num. of elem
		j.at("nne").get_to(gridParam.nne); // Num of nodes per elem
		j.at("nodof").get_to(gridParam.nodof); // Num. of deg of freedom per node
		gridParam.eldof = gridParam.nne * gridParam.nodof;

		// Nodes coordinates X and Y
		json j_geom = j["geom"];
		Initialize2dArray(gridParam.nnd, 2, gridParam.geom);
		Fill2dArrayFromJson(gridParam.nnd, 2, j_geom, gridParam.geom);

		// Element connectivity
		json j_connec = j["connec"];
		Initialize2dArray(gridParam.nnd, 2, gridParam.connec);
		Fill2dArrayFromJson(gridParam.nnd, 2, j_connec, gridParam.connec);

		// Geometrical properties 
		json j_prop = j["prop"];
		Initialize2dArray(gridParam.nel, 2, gridParam.prop);
		Fill2dArrayFromJson(gridParam.nnd, 2, j_prop, gridParam.prop);

		// Boundary conditions
		json j_nf = j["nf"];
		Initialize2dArray(gridParam.nnd, gridParam.nodof, gridParam.nf);
		Fill2dArrayFromJson(gridParam.nnd, gridParam.nodof, j_nf, gridParam.nf);
		int n = 0;
		for (int i = 0; i < gridParam.nnd; ++i)
		{
			for (int j = 0; j < gridParam.nodof; ++j)
			{
				if (gridParam.nf[i][j] != 0)
				{
					++n;
					gridParam.nf[i][j] = n;
				}
			}
		}

		// Loading
		json j_load = j["load"];
		Initialize2dArray(gridParam.nnd, 2, gridParam.load);
		Fill2dArrayFromJson(gridParam.nnd, 2, j_load, gridParam.load);

		return true;
	}
	catch(json::exception& e)
	{
		// output exception information
		std::cout << "message: " << e.what() << std::endl;
		std::cout << "exception id: " << e.id << std::endl;
		return false;
	}
}

template <typename T> 
void JsonImporter::Initialize2dArray(int rowCount, int columnCount, T**& ptr)
{
	ptr = new T * [rowCount];
	for (int i = 0; i < rowCount; ++i)
	{
		ptr[i] = new T[columnCount];
	}
}

template <typename T> 
void JsonImporter::Fill2dArrayFromJson(int rowCount, int columnCount, nlohmann::json j, T**& array2d)
{
	int row = 0;
	int col = 0;
	for (auto it = j.begin(); it != j.end(); ++it)
	{
		auto j_row = it.value();
		col = 0;
		for (auto col_iter = j_row.begin(); col_iter != j_row.end(); ++col_iter)
		{
			array2d[row][col] = col_iter.value();
			++col;
		}

		++row;
	}
}

void JsonImporter::PrintParam()
{

}
