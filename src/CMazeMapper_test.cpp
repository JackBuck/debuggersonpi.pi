/*
 * MazeMapper_test.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: jack
 */

#include "CMazeMapper.h"
#include <iostream>

using namespace std;

int CMazeMapper_test()
{
	// Test that the const pointer doesn't require the CMap to be declared const
	CMap aMap { 30, 30 };

	CMazeMapper aMazeMapper { &aMap };

	vector<int> outputRoute;
	aMazeMapper.ComputeNextVertex(aMap.GetEntranceVertex(), outputRoute);

	// Display output route
	cout << "--CMazeMapper_test--" << endl;
	if (outputRoute.size() > 0)
		cout << outputRoute[0];
	for (int i = 1; i < outputRoute.size(); ++i)
		cout << ", " << outputRoute[i];
	cout << endl;

	return 0;
}
