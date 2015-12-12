/*
 * CGraph.h
 *
 *  Created on: 13 Nov 2015
 *      Author: jack
 */

#ifndef SRC_CGRAPH_H_
#define SRC_CGRAPH_H_

#include<vector>

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
 *  - m_Order           = The order of the graph.
 *
 */
class CGraph
{
public:
	// === Constructors and Destructors =============================================================
	explicit CGraph(const std::vector<std::vector<double> >& distanceMatrix);
	virtual ~CGraph();

	// === Public Functions =========================================================================
	// Non-modifying functions
	int GetOrder() {return m_Order;}
	void Dijkstra(const unsigned int& startVertex, std::vector<double>& shortestDistances, std::vector<int>& outputRoutes);

	// === Exceptions ===============================================================================
	// TODO Derive these exceptions from a standard exception so they can be caught by generic exception handlers?
	struct InputDistMat_NotSquareMatrix
	{
		std::vector<std::vector<double> > mm_DistanceMatrix;
		InputDistMat_NotSquareMatrix(std::vector<std::vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	struct InputDistMat_InvalidElements
	{
		std::vector<std::vector<double> > mm_DistanceMatrix;
		InputDistMat_InvalidElements(std::vector<std::vector<double> > distanceMatrix)
				: mm_DistanceMatrix { distanceMatrix }
		{
		}
	};
	struct InputDistMat_MatrixTooLarge
	{
		long unsigned int mm_requestedSize;
		unsigned int mm_largestPermittedSize;
		InputDistMat_MatrixTooLarge(long unsigned int requestedSize, unsigned int largestPermittedSize)
				: mm_requestedSize {requestedSize}, mm_largestPermittedSize {largestPermittedSize}
		{
		}
	};
	struct Dijkstra_InvalidStartVertex
	{
		unsigned int mm_startVertex;
		Dijkstra_InvalidStartVertex(unsigned int startVertex)
				: mm_startVertex {startVertex}
		{
		}
	};

private:
	// === Member Variables =========================================================================
	std::vector<std::vector<double> > m_DistanceMatrix;
	std::vector<std::vector<bool> > m_AdjacencyMatrix;
	unsigned int m_Order;

};

#endif // SRC_CGRAPH_H_

