#pragma once

// c++ lib
#include<string>
#include<iostream>

// header only
#include <boost/format.hpp>
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp> 
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <nlohmann/json.hpp>

// My class
#include<GridParam.h>

using json = nlohmann::json;
using namespace boost::numeric::ublas;

class JsonImporter 
{
public:
	GridParam ReadFromJson(json& j);
	void PrintParam();
	bool isReadSuccess;

private:
	GridParam gridParam;
	template<typename T>
	void FillMatrixFromJson(json j, T& matrix);
};

