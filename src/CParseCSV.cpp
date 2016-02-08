/*
 * CParseCSV.cpp
 *
 *  Created on: 8 Feb 2016
 *      Author: Jack Buckingham
 */


#include "CParseCSV.h"
#include "CSVRow.h"
#include <fstream>

using namespace std;

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as integers.
 */
vector<vector<int> > CParseCSV::ReadCSV_int(const std::string& filePath)
{
	ifstream file(filePath);

	CSVRow row;
	vector<vector<int> > parsedFile;
	while(file >> row)
	{
		vector<int> intRow;
		for (unsigned int i = 0; i < row.size(); ++i)
		{
			int element = stoi(row[i]);
			intRow.push_back(element);
		}

		parsedFile.push_back(intRow);
	}

	return parsedFile;

}

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as doubles.
 */
vector<vector<double> > CParseCSV::ReadCSV_double(const std::string& filePath)
{
	// TODO: Most of this is c&p'd from integer version - how best should I reuse the code?

	ifstream file(filePath);

	CSVRow row;
	vector<vector<double> > parsedFile;
	while(file >> row)
	{
		vector<double> dblRow(row.size());
		for (unsigned int i = 0; i < row.size(); ++i)
		{
			double element = stod(row[i]);
			dblRow.push_back(element);
		}

		parsedFile.push_back(dblRow);
	}

	return parsedFile;
}
