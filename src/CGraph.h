/*
 * CGraph.h
 *
 *  Created on: 13 Nov 2015
 *      Author: jack
 */

#ifndef SRC_CGRAPH_H_
#define SRC_CGRAPH_H_

#include<string>
#include<vector>
#include<map>

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to represent the mathematical concept of a graph.
 * See https://en.wikipedia.org/wiki/Graph_theory
 *
 * Public Member functions:
 *  - GetOrder = A function to return the order of the graph.
 *  - Dijkstra = A public interface for internalDijkstra. It calls internalDijkstra if necessary, in
 *               order to return the shortest distance and a shortest path between two supplied
 *               vertices of the graph.
 *
 * Private Member functions:
 *  - internalDijkstra = An implementation of Dijkstra's algorithm.
 *                       https://en.wikipedia.org/wiki/Dijkstra's_algorithm
 *                       Results are saved in the member variables beginning 'm_Dijkstra'.
 *
 * Member variables:
 *  Graph Properties
 *  - m_DistanceMatrix  = A distance matrix for the graph. Use -1 to indicate an infinite distance.
 *  - m_AdjacencyMatrix = An adjacency matrix for the graph. This should be kept consistent with
 *                        distance matrix.
 *  - m_Order           = The order of the graph.
 *
 *  Dijkstra results
 *  - m_DijkstraOutputroutes      = Contains all previous output routes found when calling Dijkstra.
 *                                  The ith entry corresponds to the ith call to Dijkstra and
 *                                  contains a vector specifying the tree of shortest routes found.
 *  - m_DijkstraShortestDistances = Contains all previous shortest distances found when calling
 *                                  Dijkstra. The ith entry corresponds to the ith call to Dijkstra
 *                                  and contains a vector specifying the shortest distances between
 *                                  the start vertex and all the other vertices.
 *  - m_DijkstraStartVertices     = A map allow lookup of which index in m_DijkstraOutputroutes and
 *                                  m_DijkstraShortestDistances correspond to a requested start
 *                                  vertex.
 *
 */
enum class CGraph_DistMatCheckResult { undefined, square, lowerTriangular, upperTriangular, badShape, invalidElements, tooLarge};
class CGraph
{
public:
	// === Constructors and Destructors =============================================================
	explicit CGraph(const std::vector<std::vector<double> >& distanceMatrix, const std::vector<unsigned int> vertexLabels);
	~CGraph();

	// === Public Functions =========================================================================
	// Non-modifying functions
	unsigned int GetOrder() const {return m_Order;}

	// Dijkstra functions
	void ShortestDistance(const unsigned int& startVertex, const unsigned int& endVertex, double& shortestDistance, std::vector<unsigned int>& outputRoute);
	void ShortestDistance(const unsigned int& startVertex, const unsigned int& endVertex, const bool& preferStartVertex, double& shortestDistance, std::vector<unsigned int>& outputRoute);

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
	struct InputVertexLabels_BadSize
	{
		long unsigned int mm_vertexLabelsSize;
		InputVertexLabels_BadSize(long unsigned int vertexLabelsSize)
				: mm_vertexLabelsSize { vertexLabelsSize }
		{
		}
	};
	struct InputVertexLabels_RepeatedLabel
	{
		std::vector<unsigned int> mm_vertexLabels;
		InputVertexLabels_RepeatedLabel(std::vector<unsigned int> vertexLabels)
				: mm_vertexLabels { vertexLabels }
		{
		}
	};
	struct Dijkstra_InvalidStartVertex
	{
		unsigned int mm_startVertex;
		Dijkstra_InvalidStartVertex(unsigned int startVertex)
				: mm_startVertex { startVertex }
		{
		}
	};
	struct InternalException
	{
		std::string mm_message;
		InternalException(std::string message)
				: mm_message { message }
		{
		}
	};

private:
	// === Private Functions ========================================================================
	// External look-up functions
	unsigned int InternalToExternal(const unsigned int) const;
	void InternalToExternal(std::vector<unsigned int>&) const;
	unsigned int ExternalToInternal(const unsigned int) const;
	void ExternalToInternal(std::vector<unsigned int>&) const;

	// Dijkstra functions
	void InternalShortestDistance(const unsigned int& startVertex, const unsigned int& endVertex, const bool& preferStartVertex, double& shortestDistance, std::vector<unsigned int>& outputRoute);
	unsigned int InternalDijkstra(const unsigned int& startVertex);

	// Helper functions
	// TODO Implement this function, as well as the triangular constructor
	CGraph_DistMatCheckResult CheckInput_DistMat(std::vector<std::vector<double> >& distanceMatrix);

	// === Member Variables =========================================================================
	// Graph properties
	std::vector<std::vector<double> > m_DistanceMatrix;
	std::vector<std::vector<bool> > m_AdjacencyMatrix;
	unsigned int m_Order;

	// External vertex numbering look-up table
	std::map<unsigned int, unsigned int> m_ExternalToInternal;
	std::vector<unsigned int> m_InternalToExternal;

	// Saved Dijkstra output
	std::vector<std::vector<unsigned int> > m_DijkstraOutputRoutes;
	std::vector<std::vector<double> > m_DijkstraShortestDistances;
	std::map<unsigned int, unsigned int> m_DijkstraStartVertices;
};

#endif // SRC_CGRAPH_H_

