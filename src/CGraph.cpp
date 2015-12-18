/*
 * CGraph.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CGraph.h"
#include<iostream>
#include<limits>

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function is a constructor for the CGraph class. It takes inputs for the distance matrix.
 * distanceMatrix[i][j] should be: - the distance from vertex i to vertex j.
 *                                 - -1 if vertices i and j are not adjacent (so infinite distance)
 *
 * It checks that
 *   - The vector<vector<double> > is a matrix and is square.
 *   - The matrix is not too large. The order of the graph must fit into an unsigned integer.
 *   - The entries of the matrix are >= 0 or -1 (-1 is used to represent infinity).
 *
 * It also initialises the adjacency matrix using the distance matrix.
 *
 */
CGraph::CGraph(const vector<vector<double> > &distanceMatrix)
		: m_DistanceMatrix { distanceMatrix }, m_Order { distanceMatrix.size() }
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Check Inputs ////

	// Check distanceMatrix is not too large for m_Order to fit in an unsigned int type
	const long unsigned max_unsignedInt = std::numeric_limits<unsigned int>::max();
	if (distanceMatrix.size() > max_unsignedInt)
		throw InputDistMat_MatrixTooLarge { distanceMatrix.size(), max_unsignedInt };

	// Get dimensions and check the input is a matrix and is square
	for (unsigned int i = 0; i < m_Order; ++i)
	{
		if (distanceMatrix[i].size() > max_unsignedInt)
			throw InputDistMat_MatrixTooLarge { distanceMatrix[i].size(), max_unsignedInt };

		unsigned int rowLength = distanceMatrix[i].size();
		if (m_Order != rowLength)
		{
			throw InputDistMat_NotSquareMatrix { distanceMatrix };
		}
	}

	// Check elements are valid
	for (unsigned int i = 0; i < m_Order; ++i)
	{
		for (unsigned int j = 0; j < m_Order; ++j)
		{
			if (distanceMatrix[i][j] < 0 && distanceMatrix[i][j] != -1)
			{
				throw InputDistMat_InvalidElements { distanceMatrix };
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Create adjacency matrix ////

	// Allocate space in matrix
	m_AdjacencyMatrix.resize(m_Order);

	for (unsigned int i = 0; i < m_Order; ++i)
	{
		// Create the matrix one row at a time.
		for (unsigned int j = 0; j < m_Order; ++j)
		{
			if (distanceMatrix[i][j] >= 0 && i != j)
			{
				m_AdjacencyMatrix[i].push_back(true);
			}
			else
			{
				m_AdjacencyMatrix[i].push_back(false);
			}
		}
	}

}

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function is the destructor for the CGraph class.
 */
CGraph::~CGraph()
{
// TODO Auto-generated destructor stub
}

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function is a public wrapper for Dijkstra's algorithm.
 * It returns the shortest distance between two specified vertices, and an example shortest route
 * between them. This is done by searching for a previous appropriate set of Dijkstra outputs, and
 * calling Dijkstra if none exists.
 *
 * INPUTS:
 *
 * OUTPUTS:
 *
 *
 */
void CGraph::Dijkstra(const unsigned int& startVertex, const unsigned int& endVertex, double& shortestDistance, std::vector<unsigned int>& outputRoute)
{
	// TODO: Write this function!!
	/*
	 * Check whether we have already done Dijkstra for the start or end vertex
	 */
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function is an implementation of Dijkstra's algorithm -
 *                                                https://en.wikipedia.org/wiki/Dijkstra's_algorithm
 * It is called by the public function CGraph::Dijkstra and computes the tree of minimal routes in
 * the graph, from a specified start vertex to every other vertex in the graph. The output is stored
 * in the member variables of CGraph beginning with 'm_Dijkstra'.
 *
 * INPUTS:
 * 	startVertex - An integer to indicate the vertex of the graph from which to run the algorithm.
 * 	              Vertices of the graph will be represented by integers 0,...,n-1 where n is the
 * 	              order of the graph.
 *
 * OUTPUT:
 * 	The function returns an int which is m_DijkstraStartVertices[startVertex]. That is, it is the
 * 	index in m_DijkstraShortestDistances and m_DijkstraOutputRoutes corresponding to startVertex.
 *
 * MEMBER VARIABLES SET:
 * 	m_DijkstraShortestDistances - A vector of integers will be created which contains the shortest
 * 	              distances from the startVertex to each vertex of the graph. A value of -1 will
 * 	              be used to indicate that the vertex is not connected to startVertex.
 * 	              This vector is then appended to m_DijkstraShortestDistances.
 * 	m_DijkstraOutputRoutes - A vector of integers will be created to define examples of paths from
 * 	              the startVertex to each vertex of the graph which have the shortest total
 * 	              distance. The union of the example paths form a tree which is defined here by
 * 	              setting outputRoutes[i] to be the 'parent' of vertex i in the tree. By default,
 * 	              outputRoutes[startVertex] = startVertex. If a vertex i is not part of the same
 * 	              connected component as startVertex then outputRoutes[i] is -1.
 * 	              This vector is then appended to m_DijkstraOutputRoutes.
 * 	m_DijkstraStartVertices - A key-value pair is added in the map<int,int>
 * 	              m_DijkstraStartVertices to save the start vertex used to generate the Dijkstra
 * 	              results. The key is the startVertex and the value is the corresponding index in
 * 	              m_DijkstraShortestDistances and m_DijkstraOutputRoutes.
 *
 */
int CGraph::internalDijkstra(const unsigned int& startVertex)
{
	// -- Initial Admin -- //
	// Check startVertex is a valid vertex
	if (startVertex < 0 || startVertex >= m_Order)
	{
		throw Dijkstra_InvalidStartVertex { startVertex };
	}

	// Check whether we have already computed Dijkstra for this startVertex
	auto mapIterator = m_DijkstraStartVertices.find(startVertex);
	if (mapIterator != m_DijkstraStartVertices.end())
		return mapIterator->second; // Todo: Check this syntax does what I want!!

	// Create and initialise vectors shortestDistances and outputRoutes
	vector<double> shortestDistances(m_Order, -1);
	vector<int> outputRoutes(m_Order, -1);
	for (unsigned int i = 0; i < m_Order; ++i)
	{
		if (i == startVertex || m_AdjacencyMatrix[startVertex][i])
		{
			outputRoutes[i] = startVertex;
			shortestDistances[i] = m_DistanceMatrix[startVertex][i];
		}
	}
	outputRoutes[startVertex] = startVertex;

	// Initialise knownDistances
	vector<bool> knownDistances(m_Order, false);
	knownDistances[startVertex] = true;

	// -- Main Algorithm Body -- //
	bool moreVertices = true; // If graph is empty then startVertex will not be a valid vertex and an exception will already have been thrown
	while (moreVertices)
	{
		// Find the vertex with the shortest unconfirmed shortestDistance to startVertex
		int nextClosest = -1;
		double nextShortestDistance = -1;
		for (unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && shortestDistances[i] != -1
					&& (nextShortestDistance == -1 || shortestDistances[i] < nextShortestDistance))
			// For each vertex i for which we have not already confirmed the shortest distance to startVertex,
			// if we have a current estimate for its shortest distance to startVertex and if it is less than that of nextClosest,
			// replace nextClosest by i.
			{
				nextClosest = i;
				nextShortestDistance = shortestDistances[i];
			}
		}

		// Update shortest distances and shortest paths
		for (unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && m_AdjacencyMatrix[nextClosest][i]
					&& (shortestDistances[i] == -1
							|| shortestDistances[i] > shortestDistances[nextClosest] + m_DistanceMatrix[nextClosest][i]))
			// For each neighbour i of nextClosest whose shortest distance to startVertex we do not yet know,
			// if it is faster to go via nextClosest (or if we have no current fastest path),
			// then update shortestDistances and outputRoutes.
			{
				shortestDistances[i] = shortestDistances[nextClosest] + m_DistanceMatrix[nextClosest][i];
				outputRoutes[i] = nextClosest;
			}
		}

		// Update knownDistances
		knownDistances[nextClosest] = true;

		// Check whether there are still more
		// (if remaining vertices are all infinity then don't bother checking any more)
		moreVertices = false;
		for (unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && shortestDistances[i] != -1)
				moreVertices = true;
		}
	}

	// -- Save Results in Member Variables -- //
	m_DijkstraOutputRoutes.push_back(outputRoutes);
	m_DijkstraShortestDistances.push_back(shortestDistances);
	m_DijkstraStartVertices[startVertex] = m_DijkstraOutputRoutes.size() - 1;

	return m_DijkstraStartVertices[startVertex];
}

