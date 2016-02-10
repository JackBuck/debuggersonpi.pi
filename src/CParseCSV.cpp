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

// TODO: The functions in this file tend to be largely copy and pasted from each other. Learn how to do templates so that you can fix this!

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as integers.
 */
vector<vector<int> > CParseCSV::ReadCSV_int(const string& filePath)
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
vector<vector<double> > CParseCSV::ReadCSV_double(const string& filePath)
{
	// TODO: Most of this is c&p'd from integer version - how best should I reuse the code?

	ifstream file(filePath);
	if (!file.is_open())
		throw Exception_CantOpenFile { filePath };

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

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function appends a line (or lines) to a csv.
 */
void CParseCSV::AppendCSV(const vector<vector<int> >& line, const string& filePath)
{
	// Open the file for appending
	ofstream file(filePath, ios::app);
	if (!file.is_open())
		throw Exception_CantOpenFile { filePath };

	// Write the lines
	for (unsigned int i = 0; i < line.size(); ++i)
	{
		// Write the ith line
		for (unsigned int j = 0; j < line[i].size() - 1; ++j)
			file << line[i][j] << ',';
		if (line[i].size() > 0)
			file << line[i].back() << endl;
	}
}

void CParseCSV::AppendCSV(const vector<int>& line, const string& filePath)
{
	vector<vector<int> > temp { line };
	AppendCSV(temp, filePath);
}

void CParseCSV::AppendCSV(const vector<vector<double> >& line, const string& filePath)
{
	// Open the file for appending
	ofstream file(filePath, ios::app);
	if (!file.is_open())
		throw Exception_CantOpenFile { filePath };

	// Write the lines
	for (unsigned int i = 0; i < line.size(); ++i)
	{
		// Write the ith line
		for (unsigned int j = 0; j < line[i].size() - 1; ++j)
			file << line[i][j] << ',';
		if (line[i].size() > 0)
			file << line[i].back() << endl;
	}
}

void CParseCSV::AppendCSV(const vector<double>& line, const string& filePath)
{
	vector<vector<double> > temp { line };
	AppendCSV(temp, filePath);
}


/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Creates a csv file from a vector of vectors.
 *
 */
void CParseCSV::WriteCSV(const vector<vector<int> >& line, const string& filePath)
{
	// Open the file for appending
	ofstream file(filePath);
	if (!file.is_open())
		throw Exception_CantOpenFile { filePath };

	// Write the lines
	for (unsigned int i = 0; i < line.size(); ++i)
	{
		// Write the ith line
		for (unsigned int j = 0; j < line[i].size() - 1; ++j)
			file << line[i][j] << ',';
		if (line[i].size() > 0)
			file << line[i].back() << endl;
	}
}

void CParseCSV::WriteCSV(const vector<vector<double> >& line, const string& filePath)
{
	// Open the file for appending
	ofstream file(filePath);
	if (!file.is_open())
		throw Exception_CantOpenFile { filePath };

	// Write the lines
	for (unsigned int i = 0; i < line.size(); ++i)
	{
		// Write the ith line
		for (unsigned int j = 0; j < line[i].size() - 1; ++j)
			file << line[i][j] << ',';
		if (line[i].size() > 0)
			file << line[i].back() << endl;
	}
}


