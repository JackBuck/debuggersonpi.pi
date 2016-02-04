/*
 * CGraph_test.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
 */

#include "CGraph.h"
#include<iostream>
#include<iomanip>

using namespace std;

// For printing elements of a table
template<typename T> void printElement(T t, const int& width)
{
	const char separator = ' ';
	cout << right << setw(width) << setfill(separator) << t;
}

// Test CGraph, in particular the Dijkstra algorithm
int CGraph_test()
{
	/*TODO: Write separate checks for the constructors and ShortestDistance functions.
	 *      This will require public access to the distance matrix.
	 *      Alternatively (and better?), these test functions should be declared within the CGraph class (included by a preprocessor command perhaps) so that they have access to the private elements of the class.
	 */

	/*
	 * Contents:
	 *
	 * 1 - Define example of graph manually
	 * 2 - Define hand computed result of Dijkstra manually
	 * 3 - Call Dijkstra function in CGraph class
	 * 4 - Compare output with expected output
	 */
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	// 1 - Define example of a graph manually
	vector<vector<double> > exampleGraph_DistMat {
			{  0,  1,  3, -1, -1, -1, -1 },
			{  1,  0,  1,  4, -1, -1, -1 },
			{  3,  1,  0,  1,  1, -1,  0 },
			{ -1,  4,  1,  0,  1,  1, -1 },
			{ -1, -1,  1,  1,  0, -1, -1 },
			{ -1, -1, -1,  1, -1,  0,  1 },
			{ -1, -1,  0, -1, -1,  1,  0 }
	};

	vector<vector<double> > exampleGraph_DistMat_LT {
			{  0                         },
			{  1,  0                     },
			{  3,  1,  0                 },
			{ -1,  4,  1,  0             },
			{ -1, -1,  1,  1,  0         },
			{ -1, -1, -1,  1, -1,  0     },
			{ -1, -1,  0, -1, -1,  1,  0 }
	};

	vector<vector<double> > exampleGraph_DistMat_UT {
			{  0,  1,  3, -1, -1, -1, -1 },
			{      0,  1,  4, -1, -1, -1 },
			{          0,  1,  1, -1,  0 },
			{              0,  1,  1, -1 },
			{                  0, -1, -1 },
			{                      0,  1 },
			{                          0 }
	};

	vector<unsigned int> externalLabelling { 7, 1, 2, 3, 4, 5, 6 };
	CGraph exampleGraph { exampleGraph_DistMat, externalLabelling };
	CGraph exampleGraph_LT { exampleGraph_DistMat_LT, externalLabelling };
	CGraph exampleGraph_UT { exampleGraph_DistMat_UT, externalLabelling };


	// 2 - Define hand computed result of Dijkstra manually
	// TODO: Load these test cases from a file? As well as the above distance matrix?
	vector<unsigned int> startVertices        { 7, 7, 7, 3, 3, 7 };
	vector<unsigned int> endVertices          { 7, 3, 5, 7, 6, 3 };
	vector<double> expected_shortestDistances { 0, 3, 3, 3, 1, 3 };
	vector<vector<unsigned int> > expected_outputRoutes {
			{ 7 },
			{ 7, 1, 2, 3 },
			{ 7, 1, 2, 6, 5 },
			{ 3, 2, 1, 7 },
			{ 3, 2, 6 },
			{ 7, 1, 2, 3 }
	};
	int numTestCases = startVertices.size();

	// 3 - Call Dijkstra function in CGraph class
	vector<double> shortestDistances(numTestCases);
	vector<double> shortestDistances_LT(numTestCases);
	vector<double> shortestDistances_UT(numTestCases);
	vector<vector<unsigned int> > outputRoutes(numTestCases);
	vector<vector<unsigned int> > outputRoutes_LT(numTestCases);
	vector<vector<unsigned int> > outputRoutes_UT(numTestCases);
	for (int i = 0; i < numTestCases; ++i)
	{
		shortestDistances[i] = exampleGraph.ShortestDistance(startVertices[i], endVertices[i], outputRoutes[i]);
		shortestDistances_LT[i] = exampleGraph_LT.ShortestDistance(startVertices[i], endVertices[i], outputRoutes_LT[i]);
		shortestDistances_UT[i] = exampleGraph_UT.ShortestDistance(startVertices[i], endVertices[i], outputRoutes_UT[i]);
	}

	// 4 - Compare output with expected output
	bool success = true;
	if (expected_outputRoutes != outputRoutes || expected_outputRoutes != outputRoutes_LT || expected_outputRoutes != outputRoutes_UT)
		success = false;
	if (expected_shortestDistances != shortestDistances || expected_shortestDistances != shortestDistances_LT || expected_shortestDistances != shortestDistances_UT)
		success = false;

	// -Display output-
	// TODO: Learn how to format strings in order to nicely display expected values in brackets as well
	cout << "--CGraph_test--\n\n";

	const int colWidth_startVertex      = 12;
	const int colWidth_endVertex        = 10;
	const int colWidth_shortestDistance = 17;
	const string columnSeparator = "   ";

	// ~ From square matrix ~
	cout << "From square matrix:\n";

	// Column headers
	printElement("Start Vertex", colWidth_startVertex);
	cout << columnSeparator;
	printElement("End Vertex", colWidth_endVertex);
	cout << columnSeparator;
	printElement("Shortest Distance", colWidth_shortestDistance);
	cout << columnSeparator;
	cout << "Output Routes" << '\n';

	// Table contents
	for (int i = 0; i < numTestCases; ++i)
	{
		printElement(startVertices[i], colWidth_startVertex);
		cout << columnSeparator;
		printElement(endVertices[i], colWidth_endVertex);
		cout << columnSeparator;
		printElement(shortestDistances[i], colWidth_shortestDistance);
		cout << columnSeparator;
		for (int j = 0; j < (int) outputRoutes[i].size(); ++j)
			cout << outputRoutes[i][j] << ' ';
		cout << " (";
		for (int j = 0; j < (int) expected_outputRoutes[i].size() - 1; ++j)
			cout << expected_outputRoutes[i][j] << ' ';
		cout << expected_outputRoutes[i].back() << ')';
		cout << '\n';
	}
	cout << '\n';

	// ~ From LT matrix ~
	cout << "From lower triangular matrix:\n";

	// Column headers
	printElement("Start Vertex", colWidth_startVertex);
	cout << columnSeparator;
	printElement("End Vertex", colWidth_endVertex);
	cout << columnSeparator;
	printElement("Shortest Distance", colWidth_shortestDistance);
	cout << columnSeparator;
	cout << "Output Routes" << '\n';

	// Table contents
	for (int i = 0; i < numTestCases; ++i)
	{
		printElement(startVertices[i], colWidth_startVertex);
		cout << columnSeparator;
		printElement(endVertices[i], colWidth_endVertex);
		cout << columnSeparator;
		printElement(shortestDistances_LT[i], colWidth_shortestDistance);
		cout << columnSeparator;
		for (int j = 0; j < (int) outputRoutes_LT[i].size(); ++j)
			cout << outputRoutes_LT[i][j] << ' ';
		cout << " (";
		for (int j = 0; j < (int) expected_outputRoutes[i].size() - 1; ++j)
			cout << expected_outputRoutes[i][j] << ' ';
		cout << expected_outputRoutes[i].back() << ')';
		cout << '\n';
	}
	cout << '\n';

	// ~ From UT matrix ~
	cout << "From upper triangular matrix:\n";

	// Column headers
	printElement("Start Vertex", colWidth_startVertex);
	cout << columnSeparator;
	printElement("End Vertex", colWidth_endVertex);
	cout << columnSeparator;
	printElement("Shortest Distance", colWidth_shortestDistance);
	cout << columnSeparator;
	cout << "Output Routes" << '\n';

	// Table contents
	for (int i = 0; i < numTestCases; ++i)
	{
		printElement(startVertices[i], colWidth_startVertex);
		cout << columnSeparator;
		printElement(endVertices[i], colWidth_endVertex);
		cout << columnSeparator;
		printElement(shortestDistances_UT[i], colWidth_shortestDistance);
		cout << columnSeparator;
		for (int j = 0; j < (int) outputRoutes_UT[i].size(); ++j)
			cout << outputRoutes_UT[i][j] << ' ';
		cout << " (";
		for (int j = 0; j < (int) expected_outputRoutes[i].size() - 1; ++j)
			cout << expected_outputRoutes[i][j] << ' ';
		cout << expected_outputRoutes[i].back() << ')';
		cout << '\n';
	}
	cout << '\n';


	// Return success or failure
	if (success)
	{
		cout << "\nSuccess!\n";
		return 0;
	}
	else
	{
		cout << "\nFailure!\n";
		return 1;
	}
}
