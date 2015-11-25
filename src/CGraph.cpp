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
 *
 * It checks that
 *   - The vector<vector<double> > is a matrix and is square.
 *   - The entries of the matrix are >= 0 or -1 (-1 is used to represent infinity).
 *
 * It also initialises the adjacency matrix using the distance matrix.
 *
 */

CGraph::CGraph(const vector<vector<double> >& distanceMatrix)
		: m_DistanceMatrix { distanceMatrix }, m_Order { distanceMatrix.size() }
{
	// Get dimensions and check the input is a matrix and is square
	for (int i = 0; i < m_Order; ++i)
	{
		long unsigned int rowLength = distanceMatrix[i].size();
		if (m_Order != rowLength)
		{
			throw InputDistMat_NotSquareMatrix { distanceMatrix };
		}
	}

	// Check elements are valid
	for (int i = 0; i < m_Order; ++i)
	{
		for (int j = 0; j < m_Order; ++j)
		{
			if (distanceMatrix[i][j] < 0 && distanceMatrix[i][j] != -1)
			{
				throw InputDistMat_InvalidElements { distanceMatrix };
			}
		}
	}

	// Create adjacency matrix
	m_AdjacencyMatrix = vector < vector<int> > (m_Order);
	for (int i = 0; i < m_Order; ++i)
	{
		m_AdjacencyMatrix[i] = vector<int>(m_Order);
		for (int j = 0; j < m_Order; ++j)
		{
			if (distanceMatrix[i][j] >= 0 && i != j)
			{
				m_AdjacencyMatrix[i][j] = 1;
			}
			else
			{
				m_AdjacencyMatrix[i][j] = 0;
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
 * 	outputRoutes      - A vector of vectors of integers will be populated to contain examples of
 * 	                    paths from the startVertex to each vertex of the graph which have the
 * 	                    shortest total distance.
 *
 */
void CGraph::Dijkstra(const int& startVertex, vector<double>& shortestDistances, vector<vector<int> >& outputRoutes)
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
	shortestDistances = vector<double>(m_Order); //TODO Will this and the line below defeat the point of passing by reference?
	outputRoutes = vector < vector<int> > (m_Order);
	for (int i = 0; i < m_Order; ++i)
	{
		if (i == startVertex || m_AdjacencyMatrix[startVertex][i] == 1)
		{
			shortestDistances[i] = m_DistanceMatrix[startVertex][i];
		}
		else
		{
			shortestDistances[i] = -1;
		}
		// TODO initialise outputRoutes[i] as an empty vector (if necessary)
	}
	outputRoutes[startVertex].push_back(startVertex);

	// Initialise knownDistances
	vector<bool>
	knownDistances(m_Order);
	for (int i = 0; i < m_Order; ++i)
	{
		knownDistances[i] = false;
	}
	knownDistances[startVertex] = true;

	// -- Main algorithm body -- //
	bool moreVertices = true; // If graph is empty then startVertex will not be a valid vertex and an exception will already have been thrown
	while (moreVertices)
	{
		// Find the vertex with the shortest unconfirmed shortestDistance to startVertex
		int nextClosest = -1;
		double nextShortestDistance = -1;
		for (int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i]
					&& (nextShortestDistance == -1 || shortestDistances[i] < nextShortestDistance)) // TODO Check precedences of ! and && here!
			// For each vertex i for which we have not already confirmed the shortest distance to startVertex,
			// if our current estimate for its shortest distance to startVertex is less than that of nextClosest,
			// replace nextClosest by i.
			{
				nextClosest = i;
				nextShortestDistance = shortestDistances[i];
			}
		}

		// Update shortest distances and shortest paths
		for (int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && m_AdjacencyMatrix[nextClosest][i] == 1
					&& shortestDistances[i] > shortestDistances[nextClosest] + m_DistanceMatrix[nextClosest][i])
			// For each neighbour i of nextClosest whose shortest distance to startVertex we do not yet know,
			// if it is faster to go via nextClosest, then update shortestDistances and outputRoutes
			{
				shortestDistances[i] = shortestDistances[nextClosest] + m_DistanceMatrix[nextClosest][i];
				outputRoutes[i] = outputRoutes[nextClosest]; // Make sure that memory is copied here!
				outputRoutes[i].push_back(i);
			}
		}

		// Update knownDistances and check whether there are still more
		// (if remaining vertices are all infinity then don't bother checking any more)
		knownDistances[nextClosest] = true;

		// TODO Make this more efficient?
		moreVertices = false;
		for (int i = 0; i < m_Order; ++i)
		{
			if (!knownDistances[i] && shortestDistances[i] != -1)
				moreVertices = true;
		}
	}
}

