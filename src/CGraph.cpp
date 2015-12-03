/*
 * CGraph.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CGraph.h"
#include<iostream>

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function is a constructor for the CGraph class. It takes inputs for the distance matrix.
 * distanceMatrix[i][j] should be: - the distance from vertex i to vertex j.
 *                                 - -1 if vertices i and j are not adjacent (so infinite distance)
 *
 * It checks that
 *   - The vector<vector<double> > is a matrix and is square.
 *   - The entries of the matrix are >= 0 or -1 (-1 is used to represent infinity).
 *
 * It also initialises the adjacency matrix using the distance matrix.
 *
 */
// TODO Check that distance matrix dimensions to fit into a signed integer and cast or throw an exception accordingly
CGraph::CGraph(const vector<vector<double> > &distanceMatrix)
		: m_DistanceMatrix { distanceMatrix }, m_Order { distanceMatrix.size() }
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Check Inputs ////

	// Get dimensions and check the input is a matrix and is square
	for (long unsigned int i = 0; i < m_Order; ++i)
	{
		long unsigned int rowLength = distanceMatrix[i].size();
		if (m_Order != rowLength)
		{
			throw InputDistMat_NotSquareMatrix { distanceMatrix };
		}
	}

	// Check elements are valid
	for (long unsigned int i = 0; i < m_Order; ++i)
	{
		for (long unsigned int j = 0; j < m_Order; ++j)
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

	for (long unsigned int i = 0; i < m_Order; ++i)
	{
		// Create the matrix one row at a time.
		for (long unsigned int j = 0; j < m_Order; ++j)
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
 * This function is an implementation of Dijkstra's algorithm -
 *                                                https://en.wikipedia.org/wiki/Dijkstra's_algorithm
 * INPUTS:
 * 	startVertex       - An integer to indicate the vertex of the graph from which to run the
 * 	                    algorithm. Vertices of the graph will be represented by integers 0,...,n-1
 * 	                    where n is the order of the graph.
 *
 * OUTPUTS:
 * 	shortestDistances - A vector of integers will be populated with the shortest distances from
 * 	                    the startVertex to each vertex of the graph.
 * 	                    A value of -1 will be used to indicate that the vertex is not connected to
 * 	                    startVertex.
 * 	outputRoutes      - A vector of integers will be populated to define examples of paths from
 * 	                    the startVertex to each vertex of the graph which have the shortest total
 * 	                    distance. The union of the example paths form a tree which is defined here
 * 	                    by setting outputRoutes[i] to be the 'parent' of vertex i in the tree.
 * 	                    By default, outputRoutes[startVertex] = startVertex. If a vertex i is not
 * 	                    part of the same connected component as startVertex then outputRoutes[i]
 * 	                    is -1.
 *
 */
void CGraph::Dijkstra(const int& startVertex, vector<double>& shortestDistances, vector<int>& outputRoutes)
{
	// TODO Make outputRoutes more memory efficient (and hence speed up algorithm to avoid frequently copying lots of memory)
	// E.g. Just store the vertex you should go through next?

	// -- Initial Admin -- //
	// Check startVertex is a valid vertex
	if (startVertex < 0 || startVertex >= m_Order)
	{
		// TODO Replace this with an exception
		cerr << "Error: (CGraph::Dijkstra)\nstartVertex does not represent a valid vertex!\n";
	}

	// Delete contents of, resize and set initial values of shortestDistances and outputRoutes
	shortestDistances = vector<double>(m_Order, -1); //TODO Will this and the line below defeat the point of passing by reference?
	outputRoutes = vector<int> (m_Order, -1);
	for (long unsigned int i = 0; i < m_Order; ++i)
	{
		if (i == startVertex || m_AdjacencyMatrix[startVertex][i])
			shortestDistances[i] = m_DistanceMatrix[startVertex][i];
	}
	outputRoutes[startVertex] = startVertex;

	// Initialise knownDistances
	vector<bool> knownDistances(m_Order, false);
	knownDistances[startVertex] = true;

	// -- Main algorithm body -- //
	bool moreVertices = true; // If graph is empty then startVertex will not be a valid vertex and an exception will already have been thrown
	while (moreVertices)
	{
		// Find the vertex with the shortest unconfirmed shortestDistance to startVertex
		int nextClosest = -1;
		double nextShortestDistance = -1;
		for (long unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && shortestDistances[i] != -1
					&& (nextShortestDistance == -1 || shortestDistances[i] < nextShortestDistance)) // TODO Check precedences of ! and && here!
			// For each vertex i for which we have not already confirmed the shortest distance to startVertex,
			// if we have a current estimate for its shortest distance to startVertex and if it is less than that of nextClosest,
			// replace nextClosest by i.
			{
				nextClosest = i;
				nextShortestDistance = shortestDistances[i];
			}
		}

		// Update shortest distances and shortest paths
		for (long unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && m_AdjacencyMatrix[nextClosest][i]
					&& ( shortestDistances[i] == -1 || shortestDistances[i] > shortestDistances[nextClosest] + m_DistanceMatrix[nextClosest][i] ) )
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
		for (long unsigned int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && shortestDistances[i] != -1)
				moreVertices = true;
		}
	}
}

