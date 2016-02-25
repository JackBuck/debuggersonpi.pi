/*
 * CMazeMapper.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CMazeMapper.h"
#include "DebugLog.hpp"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

/* ~~~ FUNCTION (constructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This constructor initialises the CMazeMapper with the CMap pointer and calls Update method.
 * The update method (again!) sets the pMaze pointer and then calls FindVertsToExplore.
 *
 */
CMazeMapper::CMazeMapper(CMap* pMaze)
		: m_pCurrentMap { pMaze }
{
	DEBUG_METHOD();

	if (pMaze)
		Update(pMaze);
	else
		throw Exception_NullPointer{};
}

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function computes the route to the next vertex to explore.
 *
 *	INPUTS:
 *	currentVertex - The current vertex in the maze.
 *
 *	OUTPUTS:
 *	outputRoute - This will be populated with a fastest route from the current vertex to the next
 *		vertex to explore.
 *
 *	RETURNS:
 *	A boolean value.
 *	If true then there remain vertices to explore and outputRoute is outputted as above.
 *	If false then there are no more vertices to explore and outputRoute is set to empty.
 *
 */
bool CMazeMapper::ComputeNextVertex(const int& currentVertex, std::vector<int>& outputRoute)
{
	DEBUG_METHOD();

	// Generate graph from the CMap
	// TODO: Fix this when you now how you will generate the graph / receive the map
	vector<vector<double> > distMat = m_pCurrentMap->DistanceMatrix();
	CGraph currentGraph { distMat };

	// Check there remain vertices to explore
	if (m_vertsToExplore.size() > 0)
		return false;

	// Find closest of the vertices left to explore
	int nextVertex { m_vertsToExplore[0] };
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
		else if (newDist == currentFastestDist
				&& VertexScore(m_vertsToExplore[i]) < VertexScore(nextVertex))
		{
			// If there is a tie in distances, choose the one which is closest to the bottom left of the maze
			// If this is also a tie then do not update nextVertex. This is equivalent to choosing the vertex
			// which is closer to the top left.
			outputRoute = newOutputRoute;
			nextVertex = m_vertsToExplore[i];
		}
	}

	return true;
}

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function updates the CMazeMapper with the new map.
 * It will
 * 	- Set the pointer to the CMap
 * 	- Generate a list of vertices to explore from the CMap*
 *
 * INPUTS:
 * pNewMap - The new CMap pointer.
 *
 */
void CMazeMapper::Update(CMap* pNewMap)
{
	DEBUG_METHOD();

	if (pNewMap)
	{
		m_pCurrentMap = pNewMap;

		// Update list of vertices to explore
		FindVertsToExplore();
	}
	else
		throw Exception_NullPointer{};
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
 *
 * MEMBER VARIABLES SET:
 * m_vertsToExplore - This is updated with a list of all vertices which join a room of unknown type
 * 	to a room of known type.
 *
 */
void CMazeMapper::FindVertsToExplore()
{
	DEBUG_METHOD();

	m_vertsToExplore.clear();

	vector<vector<ERoom> > roomMap = m_pCurrentMap->GetRoomMap();

	// Add entrance vertex
	m_vertsToExplore.push_back(m_pCurrentMap->GetEntranceVertex());

	// Add vertices which join rooms of known type with those of unknown type
	for (unsigned int i = 0; i < roomMap.size(); ++i)
	{
		for (unsigned int j = 0; j < roomMap[i].size(); ++j)
		{
			if (roomMap[i][j] != ERoom_Unknown)
			{
				// Check if it leads into any unknown rooms
				vector<int> roomExits = CMap::GetRoomVertices(roomMap[i][j]);
				vector<int> roomVertexLabels = m_pCurrentMap->CalculateRoomVertices(i, j);

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

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function computes 'scores' for vertices. It is used by the ComputeNextVertex function to
 * help to decide which vertex to visit next when there is a tie for the closest vertex.
 *
 * The vertex score is computed by
 *   - Giving the vertices row and column labels in (1/2)Z
 *   - Subtracting the row label from the column label for the vertex in question
 *
 * NOTE: It *is* possible for two vertices to have the same number.
 *
 */
double CMazeMapper::VertexScore(int vertex)
{
	DEBUG_METHOD();

	vector<double> coord = m_pCurrentMap->CalculateVertexCoords(vertex);
	return coord[1] - coord[0];
}
