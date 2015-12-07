/*
 * CGraph_test.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: jack
 */

#include "CGraph.h"
#include<iostream>
#include<iomanip>

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

	CGraph exampleGraph { exampleGraph_DistMat };
	int exampleGraphOrder = 7;

	// 2 - Define hand computed result of Dijkstra manually
	// Vertex   Parent              Shortest Distance
	// 0        n/a (start vertex)  0
	// 1        0                   1
	// 2        1                   2
	// 3        2                   3
	// 4        2                   3
	// 5        6                   3
	// 6        2                   2
	vector<int> expected_outputRoutes {0, 0, 1, 2, 2, 6, 2};
	vector<double> expected_shortestDistances {0, 1, 2, 3, 3, 3, 2};

	// 3 - Call Dijkstra function in CGraph class
	// TODO Do these declarations call the default constructors?
	vector<double> shortestDistances;
	vector<int> outputRoutes;
	exampleGraph.Dijkstra(0, shortestDistances, outputRoutes);

	// 4 - Compare output with expected output
	bool success = true;
	for (int i = 0; i < exampleGraphOrder; ++i)
	{
		if (expected_outputRoutes[i] != outputRoutes[i])
			success = false;
		if (expected_shortestDistances[i] != shortestDistances[i])
			success = false;
	}

	// Display output
	cout << "--CGraph_test--\n\n";
	cout << "Output Routes:\n";
	cout << setw(10) << "Expected  ";
	for (int i = 0; i < exampleGraphOrder; ++i)
		cout << setw(3) << expected_outputRoutes[i];
	cout << '\n' << setw(10) << "Received  ";
	for (int i = 0; i < exampleGraphOrder; ++i)
		cout << setw(3) << outputRoutes[i];
	cout << '\n';

	cout << "Shortest Distances:\n";
		cout << setw(10) << "Expected  ";
		for (int i = 0; i < exampleGraphOrder; ++i)
			cout << setw(3) << expected_shortestDistances[i];
		cout << '\n' << setw(10) << "Received  ";
		for (int i = 0; i < exampleGraphOrder; ++i)
			cout << setw(3) << shortestDistances[i];
	cout << '\n';

	if (success)
		return 0;
	else
		return 1;
}
