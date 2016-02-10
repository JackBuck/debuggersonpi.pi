/*
 * CParseCSV.cpp
 *
 *  Created on: 8 Feb 2016
 *      Author: Jack Buckingham
 */


#include "CParseCSV.h"


using namespace std;

// TODO: The functions in this file tend to be largely copy and pasted from each other. Learn how to do templates so that you can fix this!

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as integers.
 */
vector<vector<int> > CParseCSV::ReadCSV_int(const string& filePath)
{
	int (*f)(const string&) = [](const string& s){return stoi(s);};
	return ReadCSV(filePath, f);
}

/* ~~~ FUNCTION (public static) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function reads an entire csv file, attempting to parse all elements as doubles.
 */
vector<vector<double> > CParseCSV::ReadCSV_double(const string& filePath)
{
	double (*f)(const string&) = [](const string& s){return stod(s);};
	return ReadCSV(filePath, f);
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


