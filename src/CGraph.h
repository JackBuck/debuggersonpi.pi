/*

 * CGraph.h
 *
 *  Created on: 13 Nov 2015
 *      Author: jack


#ifndef SRC_CGRAPH_H_
#define SRC_CGRAPH_H_

#include "../lib/Matrix.h"
#include<vector>

using namespace std;

class CGraph
{
public:
	// Constructors and destructors
	CGraph(const Numeric_lib::Matrix<bool, 2>& adjacencyMatrix, const Numeric_lib::Matrix<double, 2>& distanceMatrix);
	CGraph(const Numeric_lib::Matrix<double, 2>& distanceMatrix);
	virtual ~CGraph();

	// Non-modifying functions
	void Dijkstra(const int& startVertex, vector<double>&, vector<vector<int> >&);

private:
	Numeric_lib::Matrix<bool, 2> m_AdjacencyMatrix;
	Numeric_lib::Matrix<double, 2> m_DistanceMatrix;
};

#endif  SRC_CGRAPH_H_
*/
