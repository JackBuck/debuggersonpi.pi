/*
 * CGraph_test.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: jack
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

	vector<unsigned int> externalLabelling { 0, 1, 2, 3, 4, 5, 6 };
	CGraph exampleGraph { exampleGraph_DistMat, externalLabelling };

	// 2 - Define hand computed result of Dijkstra manually
	// TODO: Load these test cases from a file? As well as the above distance matrix?
	vector<unsigned int> startVertices        { 0, 0, 0, 3, 3, 0 };
	vector<unsigned int> endVertices          { 0, 3, 5, 0, 6, 3 };
	vector<double> expected_shortestDistances { 0, 3, 3, 3, 1, 3 };
	vector<vector<unsigned int> > expected_outputRoutes {
			{ 0 },
			{ 0, 1, 2, 3 },
			{ 0, 1, 2, 6, 5 },
			{ 3, 2, 1, 0 },
			{ 3, 2, 6 },
			{ 0, 1, 2, 3 }
	};
	int numTestCases = startVertices.size();

	// 3 - Call Dijkstra function in CGraph class
	vector<double> shortestDistances(numTestCases);
	vector<vector<unsigned int> > outputRoutes(numTestCases);
	for (int i = 0; i < numTestCases; ++i)
		exampleGraph.ShortestDistance(startVertices[i], endVertices[i], shortestDistances[i], outputRoutes[i]);

	// 4 - Compare output with expected output
	bool success = true;
	if (expected_outputRoutes != outputRoutes)
		success = false;
	if (expected_shortestDistances != shortestDistances)
		success = false;

	// -Display output-
	// TODO: Learn how to format strings in order to nicely display expected values in brackets as well
	cout << "--CGraph_test--\n\n";

	const int colWidth_startVertex      = 12;
	const int colWidth_endVertex        = 10;
	const int colWidth_shortestDistance = 17;
	const string columnSeparator = "   ";

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
		for (int j = 0; j < (int) expected_outputRoutes[i].size(); ++j)
			cout << expected_outputRoutes[i][j] << ' ';
		cout << ')';
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
