/*
 * CGraph.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CGraph.h"

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
		: m_DistanceMatrix { distanceMatrix }
{
	// Get dimensions and check the input is a matrix and is square
	int d = distanceMatrix.size();
	for (int i = 0; i < d; ++i)
	{
		int d_new = distanceMatrix[i].size();
		if (d != d_new)
		{
			throw InputDistMat_NotSquareMatrix { distanceMatrix };
		}
	}

	// Check elements are valid
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (distanceMatrix[i][j] < 0 && distanceMatrix[i][j] != -1)
			{
				throw InputDistMat_InvalidElements { distanceMatrix };
			}
		}
	}

	// Create adjacency matrix
	m_AdjacencyMatrix = vector < vector<int> > (d);
	for (int i = 0; i < d; ++i)
	{
		m_AdjacencyMatrix[i] = vector<int>(d);
		for (int j = 0; j < d; ++j)
		{
			if (distanceMatrix[i][j] >= 0)
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

CGraph::~CGraph()
{
// TODO Auto-generated destructor stub
}

void CGraph::Dijkstra(const int& startVertex, vector<double>& rShortestDistances, vector<vector<int> >& rOutputRoutes)
{
// TODO Implement Dijkstra
}

