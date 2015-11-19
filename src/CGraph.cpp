/*
 * CGraph.cpp
 *
 *  Created on: 13 Nov 2015
 *      Author: Jack Buckingham
*/

//#include "CGraph.h"
//
//CGraph::CGraph(const Numeric_lib::Matrix<bool, 2>& adjacencyMatrix,
//		const Numeric_lib::Matrix<double, 2>& distanceMatrix)
//{
//	m_AdjacencyMatrix{adjacencyMatrix};
//	m_DistanceMatrix{distanceMatrix};
//
//	//	TODO Implement check that adjacency matrix is consistent with distance matrix
//}
//
//CGraph::CGraph(const Numeric_lib::Matrix<double, 2>& distanceMatrix)
//{
//	m_DistanceMatrix { distanceMatrix };
//
//	int d1 = distanceMatrix.dim1();
//	int d2 = distanceMatrix.dim2();
//	Numeric_lib::Matrix<int, 2> adjacencyMatrix_tmp(d1, d2);
//	for (int i = 0; i < d1; ++i)
//	{
//		for (int j = 0; j < d2; ++j)
//		{
//			if (m_DistanceMatrix(i, j) >= 0)
//			{
//				adjacencyMatrix_tmp(i, j) = 1;
//			}
//			else
//			{
//				adjacencyMatrix_tmp(i, j) = 0;
//			}
//		}
//	}
//
//	m_AdjacencyMatrix { adjacencyMatrix_tmp };
//}
//
//CGraph::~CGraph()
//{
//	// TODO Auto-generated destructor stub
//}
//
//void CGraph::Dijkstra(const int& startVertex, vector<double>& rShortestDistances, vector<vector<int> >& rOutputRoutes)
//{
//	// TODO Implement Dijkstra
//}

