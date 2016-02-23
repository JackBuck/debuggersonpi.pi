/*
 * CParseCSV.cpp
 *
 *  Created on: 8 Feb 2016
 *      Author: Jack Buckingham
 */


#include "CParseCSV.h"
#include "DebugLog.hpp"

using namespace std;


/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as integers.
 */
vector<vector<int> > CParseCSV::ReadCSV_int(const string& filePath)
{
	DEBUG_METHOD();

	int (*f)(const string&) = [](const string& s){return stoi(s);};
	return ReadCSV(filePath, f);
}

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as doubles.
 */
vector<vector<double> > CParseCSV::ReadCSV_double(const string& filePath)
{
	DEBUG_METHOD();

	double (*f)(const string&) = [](const string& s){return stod(s);};
	return ReadCSV(filePath, f);
}



