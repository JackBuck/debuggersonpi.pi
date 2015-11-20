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
 *  - m_distance matrix  = A distance matrix for the graph. Use -1 to indicate an infinite distance.
 *  - m_adjacency matrix = An adjacency matrix for the graph. This should be kept consistent with
 *                         distance matrix.
 *
 *
 */
class CGraph
{
public:
	// Exceptions
	class InputDistMat_NotSquareMatrix
	{
		vector<vector<double> > mm_DistanceMatrix;
		InputDistMat_NotSquareMatrix(vector<vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	class InputDistMat_InvalidElements
	{
		vector<vector<double> > mm_DistanceMatrix;
		InputDistMat_InvalidElements(vector<vector<double> > distanceMatrix)
				: mm_DistanceMatrix
						{ distanceMatrix }
		{
		}
	};

	// Constructors and destructors
	CGraph(const vector<vector<double> >& distanceMatrix);
	virtual ~CGraph();

	// Non-modifying functions
	void Dijkstra(const int& startVertex, vector<double>&, vector<vector<int> >&);

private:
	vector<vector<bool> > m_AdjacencyMatrix;
	vector<vector<double> > m_DistanceMatrix;
};

#endif // SRC_CGRAPH_H_

