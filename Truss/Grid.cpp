#include "Grid.h"

bool Grid::ReadFromJson(json& j)
{
	j.at("nnd").get_to(nnd);
	j.at("nel").get_to(nel);
	j.at("nne").get_to(nne);
	j.at("nodof").get_to(nodof);
	eldof = nne * nodof;

	return true;
}
