#pragma once

#include<string>
#include<iostream>

#include <nlohmann/json.hpp>

#include<GridParam.h>

using json = nlohmann::json;

class JsonImporter 
{
public:

	GridParam gridParam;
	bool ReadFromJson(json& j);
	void PrintParam();

private:
	template <typename T>
	void Initialize2dArray(int rowcount, int columnCount, T**& ptr);
	template <typename T>
	void Fill2dArrayFromJson(int rowCount, int columnCount, nlohmann::json j, T**& array2d);
};

