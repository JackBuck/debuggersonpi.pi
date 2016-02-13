/*
 * CMazeMapper.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CMazeMapper.h"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

/* ~~~ FUNCTION (constructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 */
CMazeMapper::CMazeMapper(const CMap& maze)
{
	Update(maze);
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
void CMazeMapper::ComputeNextVertex(const int& currentVertex, std::vector<int>& outputRoute)
{
	/* Algorithm outline
	 * - Find closest of vertices left to explore. Compute shortest routes as you go along.
	 */



	// Find closest of vertices left to explore
	int nextVertex {m_vertsToExplore[0]};
	double currentFastestDist = m_currentGraph.ShortestDistance(currentVertex, m_vertsToExplore[0], true, outputRoute);
	for (unsigned int i = 1; i < m_vertsToExplore.size(); ++i)
	{
		vector<int> newOutputRoute;
		double newDist = m_currentGraph.ShortestDistance(currentVertex, m_vertsToExplore[i], true, newOutputRoute);

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

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function updates the CMazeMapper with the new map.
 * It will
 * 	- Generate a graph from the CMap
 * 	- Generate a list of vertices to explore from the CMap
 *
 * INPUTS:
 * newMap - The new CMap object.
 *
 */
void CMazeMapper::Update(const CMap& newMap)
{
	// Generate graph from the maze
	// TODO: Fix this when you now how you will generate the graph / receive the map
	vector< vector<double> > distanceMatrix;
	vector<int> vertexLabels;
	m_currentGraph = CGraph { distanceMatrix, vertexLabels };

	// Update list of vertices to explore
	FindVertsToExplore(newMap);
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function analyses a map and computes a vector of vertices to explore.
 *
 * A vertex is added to the vector if it joins a room of unknown type to a room with known type.
 *
 * BE WARNED -- Vertices added need not be in the same connected component as the robot! Indeed,
 *    this will occur if two rooms of CMap of known type are not joined by rooms of known type. For
 *    example, if we add the types of the start and end rooms (to prevent the robot from exploring
 *    them and getting lost over the white spot) then they will initially be unconnected.
 *
 * IMPORTANT -- The rooms in the maze which lead to the entrance and exit from the maze should be
 *    passed with known type. If a room at the edge of the maze leads out of the maze then overflow
 *    exceptions will occur.
 *
 * INPUTS:
 * newMap - This should be a CMap from which to compute the next vertices to explore.
 *
 * MEMBER VARIABLES SET:
 * m_vertsToExplore - This is updated with a list of all vertices which join a room of unknown type
 * 	to a room of known type.
 *
 */
void CMazeMapper::FindVertsToExplore(const CMap& newMap)
{
	m_vertsToExplore.clear();

	vector<vector<ERoom> > roomMap = newMap.GetRoomMap();

	for (unsigned int i = 0; i < roomMap.size(); ++i)
	{
		for (unsigned int j = 0; j < roomMap[i].size(); ++j)
		{
			if (roomMap[i][j] != ERoom_Unknown)
			{
				// Check if it leads into any unknown rooms
				vector<int> roomExits = CMap::GetRoomVertices(roomMap[i][j]);
				vector<int> roomVertexLabels = newMap.CalculateRoomVertices(i, j);

				// Check room above
				if (roomExits[0] == 1 && roomMap.at(i-1)[j] == ERoom_Unknown)
				{
					m_vertsToExplore.push_back(roomVertexLabels[0]);
				}

				// Check room to the right
				if (roomExits[1] == 1 && roomMap[i].at(j+1) == ERoom_Unknown)
				{
					m_vertsToExplore.push_back(roomVertexLabels[1]);
				}

				// Check room below
				if (roomExits[2] == 1 && roomMap.at(i+1)[j] == ERoom_Unknown)
				{
					m_vertsToExplore.push_back(roomVertexLabels[2]);
				}

				// Check room to left
				if (roomExits[3] == 1 && roomMap[i].at(j-1) == ERoom_Unknown)
				{
					m_vertsToExplore.push_back(roomVertexLabels[3]);
				}

			}
		}
	}
}

