#include "JsonImporter.h"

GridParam JsonImporter::ReadFromJson(json& j)
{
	try
	{
		j.at("nnd").get_to(gridParam.nnd); // Num. of nodes
		j.at("nel").get_to(gridParam.nel); // Num. of elem
		j.at("nne").get_to(gridParam.nne); // Num of nodes per elem
		j.at("nodof").get_to(gridParam.nodof); // Num. of deg of freedom per node
		gridParam.eldof = gridParam.nne * gridParam.nodof; // Num

		// Nodes coordinates X and Y
		json j_geom = j["geom"];
		gridParam.geom = matrix<double>(gridParam.nnd, 2);
		FillMatrixFromJson(j_geom, gridParam.geom);


		// Element connectivity
		json j_connec = j["connec"];
		gridParam.connec = matrix<int>(gridParam.nnd, 2);
		FillMatrixFromJson(j_connec, gridParam.connec);

		// Geometrical properties 
		json j_prop = j["prop"];
		gridParam.prop = matrix<double>(gridParam.nel, 2);
		FillMatrixFromJson(j_prop, gridParam.prop);

		// Boundary conditions
		json j_nf = j["nf"];
		gridParam.nf = matrix<double>(gridParam.nnd, gridParam.nodof);
		FillMatrixFromJson(j_nf, gridParam.nf);
		int n = 0;
		for (int i = 0; i < gridParam.nnd; ++i)
		{
			for (int j = 0; j < gridParam.nodof; ++j)
			{
				if (gridParam.nf(i, j) != 0)
				{
					++n;
					gridParam.nf(i, j) = n;
				}
			}
		}
		gridParam.n = n;

		// Loading
		json j_load = j["load"];
		gridParam.load = matrix<double>(gridParam.nnd, 2);
		FillMatrixFromJson(j_load, gridParam.load);

		this->isReadSuccess = true;
	}
	catch (json::exception & e)
	{
		// output exception information
		std::cout << "[Exception] from nlohmann/json.hpp " << std::endl;
		std::cout << "message: " << e.what() << std::endl;
		std::cout << "exception id: " << e.id << std::endl;
		
		this->isReadSuccess = false;
	}
	return gridParam;
}

void JsonImporter::PrintParam()
{
	try
	{
		std::cout << boost::format{ "nnd = %1% " } % gridParam.nnd << std::endl;
		std::cout << boost::format{ "nel = %1% " } % gridParam.nel << std::endl;
		std::cout << boost::format{ "nne = %1% " } % gridParam.nne << std::endl;
		std::cout << boost::format{ "nodof = %1% " } % gridParam.nodof << std::endl;
		std::cout << boost::format{ "eldof = %1% " } % gridParam.eldof << std::endl;
		std::cout << "geom = " << std::endl;
		std::cout << gridParam.geom << std::endl;
		std::cout << "connec = " << std::endl;
		std::cout << gridParam.connec << std::endl;
		std::cout << "prop = " << std::endl;
		std::cout << gridParam.prop << std::endl;
		std::cout << "nf = " << std::endl;
		std::cout << gridParam.nf << std::endl;
		std::cout << "load = " << std::endl;
		std::cout << gridParam.load << std::endl;
	}
	catch (boost::exception & e)
	{
		std::cout << "[Exception] from boost " << std::endl;
		std::cout << boost::diagnostic_information(e) << std::endl;
	}
}

template<typename T>
void JsonImporter::FillMatrixFromJson(json j, T& m)
{
	int row = 0;
	int col = 0;
	for (auto it = j.begin(); it != j.end(); ++it)
	{
		auto j_row = it.value();
		col = 0;
		for (auto col_iter = j_row.begin(); col_iter != j_row.end(); ++col_iter)
		{
			m(row, col) = col_iter.value();
			++col;
		}
		++row;
	}
}



