/*
 * CMazeMapper.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CMazeMapper.h"
#include "CGraph.h"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

/* ~~~ FUNCTION (constructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 */
CMazeMapper::CMazeMapper()
{
	// TODO Auto-generated constructor stub

}

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function computes the route to the next vertex to explore.
 *
 *	INPUTS:
 *	currentMap - A CMap object representing the best map of the maze we currently have.
 *	currentVertex - The current vertex in the maze.
 *
 *	OUTPUTS:
 *	outputRoute - This will be populated with a fastest route from the current vertex to the next
 *		vertex to explore.
 *
 */
void CMazeMapper::ComputeNextVertex(const CMap& currentMap, const int& currentVertex, std::vector<int>& outputRoute)
{
	/* Algorithm outline
	 * - Either: generate graph from CMap, get passed graph instead of CMap or access graph as member variable of CMap
	 * - Find closest of vertices left to explore. Compute shortest routes as you go along.
	 */

	// Get CGraph somehow!
	// TODO: Fix this when you now how you will generate the graph / receive the map
	vector< vector<double> > distanceMatrix;
	vector<int> vertexLabels;
	CGraph currentGraph {distanceMatrix, vertexLabels};

	// Find closest of vertices left to explore
	int nextVertex {m_vertsToExplore[0]};
	double currentFastestDist = currentGraph.ShortestDistance(currentVertex, m_vertsToExplore[0], true, outputRoute);
	for (unsigned int i = 1; i < m_vertsToExplore.size(); ++i)
	{
		vector<int> newOutputRoute;
		double newDist = currentGraph.ShortestDistance(currentVertex, m_vertsToExplore[i], true, newOutputRoute);

		if (newDist < currentFastestDist)
		{
			currentFastestDist = newDist;
			outputRoute = newOutputRoute;
			nextVertex = m_vertsToExplore[i];
		}
		else if (newDist == currentFastestDist //&& TODO: Fill in this condition once you know how the vertices are numbered
				/* You could do this using the sum of the coordinates of the vertex in the maze. I.e. Coordinates would be even for room edge and odd for room middle (zero based index), so one coord. in each pair would have to be even.*/
				)
		{
			// If there is a tie in distances, choose the one which is closest to the bottom left of the maze
			outputRoute = newOutputRoute;
			nextVertex = m_vertsToExplore[i];
		}
	}


}

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function analyses a map and computes a vector of vertices to explore.
 *
 * INPUTS:
 * newMap - This should be a CMap from which to compute the next vertices to explore.
 *
 */
void CMazeMapper::AnalyseMap(const CMap& newMap)
{
	m_vertsToExplore.clear();

	vector<vector<ERoom> > roomMap = newMap.GetRoomMap(); // TODO: For some reason the compiler doesn't think this is a vector of vectors of ERooms...

	for (unsigned int i = 0; i < roomMap.size(); ++i)
	{
		for (unsigned int j = 0; j < roomMap[i].size(); ++j)
		{
			if (roomMap[i][j] != ERoom_Unknown)
			{
				// Check if it leads into any unknown rooms
				vector<int> roomExits = CMap::GetRoomVertices(roomMap[i][j]);

				// Check room above
				if (roomExits[0] == 1 && roomMap[i-1][j] == ERoom_Unknown)
				{
					int vertAbove = 0; // TODO: Compute this properly -- use a static method in CMap?
					m_vertsToExplore.push_back(vertAbove);
				}

				// Check room to the right
				if (roomExits[1] == 1 && roomMap[i][j+1] == ERoom_Unknown)
				{
					int vertToRight = 0; // TODO: Compute this properly -- use a static method in CMap?
					m_vertsToExplore.push_back(vertToRight);
				}

				// Check room below
				if (roomExits[2] == 1 && roomMap[i+1][j] == ERoom_Unknown)
				{
					int vertBelow = 0; // TODO: Compute this properly -- use a static method in CMap?
					m_vertsToExplore.push_back(vertBelow);
				}

				// Check room to left
				if (roomExits[3] == 1 && roomMap[i][j-1] == ERoom_Unknown)
				{
					int vertToLeft = 0; // TODO: Compute this properly -- use a static method in CMap?
					m_vertsToExplore.push_back(vertToLeft);
				}

			}
		}
	}
}

