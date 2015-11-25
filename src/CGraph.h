/*
 * CGraph.h
 *
 *  Created on: 13 Nov 2015
 *      Author: jack
 */

#ifndef SRC_CGRAPH_H_
#define SRC_CGRAPH_H_

#include<vector>

using namespace std;

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to represent the mathematical concept of a graph.
 * See https://en.wikipedia.org/wiki/Graph_theory
 *
 * Member functions:
 *  - Dijkstra = An implementation of Dijkstra's algorithm.
 *               https://en.wikipedia.org/wiki/Dijkstra's_algorithm
 *
 * Member variables:
 *  - m_DistanceMatrix  = A distance matrix for the graph. Use -1 to indicate an infinite distance.
 *  - m_AdjacencyMatrix = An adjacency matrix for the graph. This should be kept consistent with
 *                        distance matrix.
 *
 */
class CGraph
{
public:
	// === Constructors and Destructors =============================================================
	CGraph(const vector<vector<double> >& distanceMatrix);
	virtual ~CGraph();

	// === Public Functions =========================================================================
	// Non-modifying functions
	void Dijkstra(const int& startVertex, vector<double>& shortestDistances, vector<vector<int> >& outputRoutes);

	// === Exceptions ===============================================================================
	// TODO Derive these exceptions from a standard exception so they can be caught by generic exception handlers?
	struct InputDistMat_NotSquareMatrix
	{
		vector<vector<double> > mm_DistanceMatrix;
		InputDistMat_NotSquareMatrix(vector<vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	struct InputDistMat_InvalidElements
	{
		vector<vector<double> > mm_DistanceMatrix;
		InputDistMat_InvalidElements(vector<vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};

private:
	// === Member Variables =========================================================================
	vector<vector<double> > m_DistanceMatrix;
	vector<vector<bool> > m_AdjacencyMatrix;
	long unsigned int m_Order;

};

#endif // SRC_CGRAPH_H_

