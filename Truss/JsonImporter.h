#pragma once

// c++ lib
#include<string>
#include<iostream>

// header only
#include <boost/format.hpp>
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp> 
#include <nlohmann/json.hpp>

// My class
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
	template <typename T>
	std::string Print2dArray(int rowCount, int columnCount, T** ptr);
};

