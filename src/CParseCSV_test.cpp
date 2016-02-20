/*
 * CParseCSV_test.cpp
 *
 *  Created on: 8 Feb 2016
 *      Author: jack
 */

#include "CParseCSV.h"
#include <iostream>
#include <vector>
#include <string>
#include "DebugLog.hpp"


using namespace std;

// Test the static functions in CParseCSV
int CParseCSV_test()
{
	DEBUG_METHOD();

	cout << "--CParseCSV_test--\n\n";

	// Define something to save (incidentally the distance matrix from CGraph_test()
	vector<vector<int> > infoForCSV {
		{  0,  1,  3, -1, -1, -1, -1 },
		{  1,  0,  1,  4, -1, -1, -1 },
		{  3,  1,  0,  1,  1, -1,  0 },
		{ -1,  4,  1,  0,  1,  1, -1 },
		{ -1, -1,  1,  1,  0, -1, -1 },
		{ -1, -1, -1,  1, -1,  0,  1 }
	};

	vector<int> extraLine { -1, -1,  0, -1, -1,  1,  0 };


	// Save it
	string testCSVFilePath {"TestData/TestCSVFile.csv"};
	CParseCSV::WriteCSV(infoForCSV, testCSVFilePath);
	CParseCSV::WriteCSV(extraLine, testCSVFilePath, ios::app);

	// Read it
	vector<vector<int> > reloadedInfo = CParseCSV::ReadCSV_int(testCSVFilePath);

	// Compare the two
	int result {0};

	vector<vector<int> > expectedReloadedInfo { infoForCSV };
	expectedReloadedInfo.push_back(extraLine);

	if (expectedReloadedInfo.size() != reloadedInfo.size())
	{
		cout << "Loaded file size (" << reloadedInfo.size() << ") does not match saved file size (" << expectedReloadedInfo.size() << ")\n";
		result = 1;
	}
	else
	{
		for (unsigned int i = 0; i < reloadedInfo.size(); ++i)
		{
			if (expectedReloadedInfo[i].size() != reloadedInfo[i].size())
			{
				cout << "Loaded file line " << i << " length (" << reloadedInfo[i].size() << ") does not match saved line length (" << expectedReloadedInfo[i].size() << ")\n";
				result = 1;
			}
			else
			{
				for (unsigned int j = 0; j < reloadedInfo[i].size(); ++j)
				{
					if (expectedReloadedInfo[i][j] != reloadedInfo[i][j])
					{
						cout << "Loaded element (" << i << ',' << j << ") is " << reloadedInfo[i][j] << " and does not match saved element " << expectedReloadedInfo[i][j] << '\n';
						result = 1;
					}
				}
			}

		}
	}

	// Report success
	if (result == 0)
		cout << "\nSuccess!\n";
	else
		cout << "\nFailure.\n";

	return result;
}

void CParseCSV_test2()
{
	DEBUG_METHOD();

	string filePath = "TestData/PracticeMap.csv";

	vector<vector<int> > practiceMap = CParseCSV::ReadCSV_int(filePath);

	cout << "--CParseCSV_test2--\n\n";

	cout << "Loaded size " << practiceMap.size() << 'x' << practiceMap[0].size() << "\n\n";

	for (unsigned int i = 0; i < practiceMap.size(); ++i)
	{
		for (unsigned int j = 0; j < practiceMap[i].size(); ++j)
		{
			cout << practiceMap[i][j];
			if (j < practiceMap[i].size()-1)
				cout << ',';
		}
		cout << '\n';
	}

}
