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

CGraph::CGraph(const vector<vector<double> > &distanceMatrix)
//		: m_DistanceMatrix { distanceMatrix }
{
	// Get dimensions and check the input is a matrix and is square
	int matrix_size = distanceMatrix.size();   // Changed this more to make more obvious no need for reference its just an integer
	for (int i = 0; i < matrix_size; ++i)
	{
		if (matrix_size != distanceMatrix[i].size())
		{
			throw InputDistMat_NotSquareMatrix { distanceMatrix };
		}
	}

	// Check elements are valid
	for (int i = 0; i < matrix_size; ++i)
	{
		for (int j = 0; j < matrix_size; ++j)
		{
			if (distanceMatrix[i][j] < 0 && distanceMatrix[i][j] != -1)
			{
				throw InputDistMat_InvalidElements { distanceMatrix };
			}
		}
	}

	//// Create adjacency matrix
	//m_AdjacencyMatrix = vector(d);
	//for (int i = 0; i < d; ++i)
	//{
	//	m_AdjacencyMatrix[i] = vector(d);
	//	for (int j = 0; j < d; ++j)
	//	{
	//		if (distanceMatrix[i][j] >= 0)
	//		{
	//			m_AdjacencyMatrix[i][j] = 1;
	//		}
	//		else
	//		{
	//			m_AdjacencyMatrix[i][j] = 0;
	//		}
	//	}
	//}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Hannah's Version

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate space in matrix
	m_AdjacencyMatrix.resize(matrix_size);

	for (int i = 0; i < matrix_size; ++i)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//// Create temporary vector to contain row.

		for (int j = 0; j < matrix_size; ++j)
		{
			if (distanceMatrix[i][j] >= 0)
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

CGraph::~CGraph()
{
// TODO Auto-generated destructor stub
}

void CGraph::Dijkstra(const int& startVertex, vector<double>& rShortestDistances, vector<vector<int> >& rOutputRoutes)
{
// TODO Implement Dijkstra
}

