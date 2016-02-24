////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Instructions.h"
#include "Signals.h"
#include "Manouvre.h"
#include<iostream>
#include<fstream>
#include <cmath>
#include "EnumsHeader.h"
#include "DebugLog.hpp"
#include "CMap.h"
#include "CParseCSV.h"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//int ENTRANCEPORCHROOM = -1;



// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is a constructor for the CMap Class. It takes the filepath of the raw input data
// and from this creates an instance of the class.
CMap::CMap(string filepath)
{
	DEBUG_METHOD();

	m_cellMap = CParseCSV::ReadCSV_int(filepath);

	m_cellwidth = m_cellMap.size();
	m_cellheight = m_cellwidth;

	CreateRoomMap();
	ComputeCellMapSize();

	//////////////////////////////////////////////////////////////////////////////////////
	// Entrance and exit predefined

	m_firstRoom = m_cellheight*m_cellwidth;
	m_exitRoom = m_cellwidth-1;

	m_entranceCell = {3*m_firstRoom , 2};
	m_exitCell = {2, 3*m_cellwidth}; // TODO: Change this? The exit cell is

	//////////////////////////////////////////////////////////////////////////////////////
	// Assume positioned at start.

	m_currentVertex = GetEntranceVertex();
	DEBUG_VALUE_OF_LOCATION(m_currentVertex);

	m_currentOrientation = EOrientation_North;
	DEBUG_VALUE_OF_LOCATION(m_currentOrientation);
	
	///////////////////////////////////////////////////////////////////////////////////////
	// Initial 'next room' is entrance room is the bottom left room on the map
	m_nextRoom = vector<int> {m_cellheight/3 -1, 0};
	//m_nextRoom[0] = ENTRANCEPORCHROOM;
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialiser for unknown map.
CMap::CMap(int room_height, int room_width)
{
	DEBUG_METHOD();

	m_cellMap = vector<vector<int>> (room_height * 3, vector<int>(room_width * 3));

	for(int i=0; i<room_height; i++)
	{
		for(int j=0; j<room_width; j++)
		{
			m_cellMap[3*i][3*j] = 0;
			m_cellMap[3*i+2][3*j] = 0;
			m_cellMap[3*i][3 * j+2] = 0;
			m_cellMap[3*i+2][3 * j+2] = 0;
			m_cellMap[3*i+1][3 * j+1] = -1;
			m_cellMap[3*i][3*j+1] = -1;
			m_cellMap[3*i+1][3*j+2] = -1;
			m_cellMap[3*i+2][3*j+1] = -1;
			m_cellMap[3*i + 1][3*j] = -1;

		}
	}

	m_exitRoom = room_width -1;
	m_firstRoom = room_width * (room_height - 1);

	ComputeCellMapSize();

	///////////////////////////////////////////////////////////////////////////////////////
	// Initial 'next room' is entrance room is the bottom left room on the map
	m_nextRoom = vector<int> {m_cellheight/3 -1, 0};
	m_currentVertex = GetEntranceVertex();
	DEBUG_VALUE_OF_LOCATION(m_currentVertex);
	m_currentOrientation = EOrientation_North;
	DEBUG_VALUE_OF_LOCATION(m_currentOrientation);

	CreateRoomMap();
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function creates the room map from a cell map.
void CMap::CreateRoomMap()
{

	DEBUG_METHOD();

	int room_height = m_cellheight/3;
	int room_width = m_cellwidth/3;

	for(int height_index=0; height_index<room_height; height_index++)
	{ 
		for(int width_index=0; width_index<room_width; width_index++)
		{
			//////////////////////////////////////////////////////////
			// Check that the room is not empty
			if ((m_cellMap[3*height_index][3*width_index + 1] == -1)                  // north
					|| (m_cellMap[(3*height_index) + 1][(3*width_index) + 2] == -1)     // east
					|| (m_cellMap[(3 * height_index) + 2][(3 * width_index) + 1] == -1) // south
					|| (m_cellMap[(3*height_index) + 1][(3*width_index)] == -1))        // west
			{
				if (width_index == 0)
				{
					vector<ERoom> temp_vec;
					temp_vec.clear();
					temp_vec.push_back(ERoom_Unknown);
					m_roomMap.push_back(temp_vec);
				}
				else
				{
					m_roomMap[height_index].push_back(ERoom_Unknown);
				}

				continue;
			}


			//////////////////////////////////////////////////////////
			// Determine room type
			vector<bool> room_flag;
			room_flag.assign(16, true);

			if(m_cellMap[(3*height_index)][(3*width_index) + 1] == 0) // Check north vertex
			{ 
				room_flag[ERoom_Cross] = false;
				room_flag[ERoom_North] = false;
				room_flag[ERoom_NorthEast] = false;
				room_flag[ERoom_NorthSouth] = false;
				room_flag[ERoom_NorthWest] = false;
				room_flag[ERoom_NorthEastSouth] = false;
				room_flag[ERoom_NorthSouthWest] = false;
				room_flag[ERoom_NorthEastWest] = false;
				
			}
			else
			{
				room_flag[ERoom_Empty] = false; 
				room_flag[ERoom_East] = false;
				room_flag[ERoom_South] = false;
				room_flag[ERoom_West] = false;
				room_flag[ERoom_EastSouth] = false;
				room_flag[ERoom_SouthWest] = false;
				room_flag[ERoom_EastWest] = false;
				room_flag[ERoom_EastSouthWest] = false;
			}

			if (m_cellMap[(3*height_index) + 1][(3*width_index) + 2] == 0) // Check east vertex
			{
				room_flag[ERoom_Cross] = false;
				room_flag[ERoom_East] = false;
				room_flag[ERoom_EastSouth] = false;
				room_flag[ERoom_EastWest] = false;
				room_flag[ERoom_NorthEast] = false;
				room_flag[ERoom_NorthEastSouth] = false;
				room_flag[ERoom_EastSouthWest] = false;
				room_flag[ERoom_NorthEastWest] = false;
			}
			else
			{
				room_flag[ERoom_Empty] = false;
				room_flag[ERoom_North] = false;
				room_flag[ERoom_South] = false;
				room_flag[ERoom_West] = false;
				room_flag[ERoom_NorthSouth] = false;
				room_flag[ERoom_SouthWest] = false;
				room_flag[ERoom_NorthWest] = false;
				room_flag[ERoom_NorthSouthWest] = false;
			}

			if (m_cellMap[(3 * height_index) + 2][(3 * width_index) + 1] == 0) // Check south vertex
			{
				room_flag[ERoom_Cross] = false;
				room_flag[ERoom_South] = false;
				room_flag[ERoom_NorthSouth] = false;
				room_flag[ERoom_SouthWest] = false;
				room_flag[ERoom_EastSouth] = false;
				room_flag[ERoom_NorthEastSouth] = false;
				room_flag[ERoom_NorthSouthWest] = false;
				room_flag[ERoom_EastSouthWest] = false;
			}
			else
			{
				room_flag[ERoom_Empty] = false;
				room_flag[ERoom_East] = false;
				room_flag[ERoom_North] = false;
				room_flag[ERoom_West] = false;
				room_flag[ERoom_NorthEast] = false;
				room_flag[ERoom_NorthWest] = false;
				room_flag[ERoom_EastWest] = false;
				room_flag[ERoom_NorthEastWest] = false;
			}
			
			if (m_cellMap[(3*height_index) + 1][(3*width_index)] == 0) // Check west vertex
			{
				room_flag[ERoom_Cross] = false;
				room_flag[ERoom_West] = false;
				room_flag[ERoom_EastWest] = false;
				room_flag[ERoom_NorthWest] = false;
				room_flag[ERoom_SouthWest] = false;
				room_flag[ERoom_NorthEastWest] = false;
				room_flag[ERoom_NorthSouthWest] = false;
				room_flag[ERoom_EastSouthWest] = false;

			}
			else
			{
				room_flag[ERoom_Empty] = false;
				room_flag[ERoom_East] = false;
				room_flag[ERoom_South] = false;
				room_flag[ERoom_North] = false;
				room_flag[ERoom_EastSouth] = false;
				room_flag[ERoom_NorthSouth] = false;
				room_flag[ERoom_NorthEast] = false;
				room_flag[ERoom_NorthEastSouth] = false;
			}


			//////////////////////////////////////////////////////////
			// There should now only be one true flag.

			int count = 0;

			for(int i=0; i<16; i++)
			{
				if(room_flag[i])
				{
					count++;
					ERoom temp_room = static_cast<ERoom>( i );
					vector<ERoom> temp_vec;

					if (width_index == 0)
					{
						temp_vec.clear();
						temp_vec.push_back(temp_room);
						m_roomMap.push_back(temp_vec);
					}
					else
					{
						m_roomMap[height_index].push_back(temp_room);
					}
				}
			}
		}

	}

}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CMap::ComputeCellMapSize()
{
	DEBUG_METHOD();

	m_cellheight= m_cellMap.size();
	if(m_cellheight > 0)	m_cellwidth = m_cellMap[0].size();
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<vector<ERoom>> CMap::GetRoomMap() const
{
	DEBUG_METHOD();

	return m_roomMap;
}

ERoom CMap::GetRoomType(int room_index) const
{
	DEBUG_METHOD();

	vector<int> coords = RoomIndextoCoord(room_index);
	return m_roomMap[coords[0]][coords[1]];
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<vector<int>> CMap::GetCellMap() const
{
	DEBUG_METHOD();
	
	return m_cellMap;
}

int CMap::GetEntranceRoom() const
{
	DEBUG_METHOD();

	return m_firstRoom;
}

int CMap::GetExitRoom() const
{
	DEBUG_METHOD();
	
	return m_exitRoom;
}

vector<int> CMap::GetEntranceCell() const
{
	DEBUG_METHOD();

	return m_entranceCell;
}

vector<int> CMap::GetExitCell() const
{
	DEBUG_METHOD();

	return m_exitCell;
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CMap::UpdateRoomMap()
{
	DEBUG_METHOD();
	CreateRoomMap();
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CMap::UpdateCellMap()
{
	DEBUG_METHOD();
	m_cellMap.clear();
	m_cellMap.resize(m_roomMap.size()*3);

	for(size_t i=0; i<m_roomMap.size(); i++)
	{ 
		for (int cell_index=0; cell_index<3; cell_index++)
		{
			m_cellMap[3*i+cell_index].resize(m_roomMap[i].size()*3);
		}
		

		for (size_t j = 0; j < m_roomMap[i].size(); j++)
		{

			m_cellMap[3*i][3*j] = 0;     // top left corner
			m_cellMap[3*i+2][3*j] = 0;   // bottom left corner
			m_cellMap[3*i][3*j+2] = 0;   // top right corner
			m_cellMap[3*i+2][3*j+2] = 0; // bottom right corner
			m_cellMap[3*i+1][3*j+1] = 1; // room centre


			switch (m_roomMap[i][j])
			{
				case ERoom_Empty:
				{
					m_cellMap[3*i+1][3*j+1] = 0; // room centre
					break;
				}
				case ERoom_Cross:
				{
					m_cellMap[3*i][3*j+1]   = 1; // middle top
					m_cellMap[3*i+1][3*j+2] = 1; // right centre
					m_cellMap[3*i+2][3*j+1] = 1; // middle bottom
					m_cellMap[3*i+1][3*j]   = 1; // left centre
					break;
				}
				case ERoom_North:
				{
					m_cellMap[3*i][3*j+1] = 1;
					break;
				}
				case ERoom_East:
				{
					m_cellMap[3*i + 1][3*j + 2] = 1;
					break;
				}
				case ERoom_South:
				{
					m_cellMap[3*i + 2][3*j + 1] = 1;
					break;
				}
				case ERoom_West:
				{
					m_cellMap[3*i + 1][3*j] = 1;
					break;
				}
				case ERoom_NorthEast:
				{
					m_cellMap[3*i][3*j + 1] = 1;
					m_cellMap[3*i + 1][3*j + 2] = 1;
					break;
				}
				case ERoom_NorthSouth:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					break;
				}
				case ERoom_NorthWest:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_EastSouth:
				{
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					break;
				}
				case ERoom_EastWest:
				{
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_SouthWest:
				{
					m_cellMap[3*i+2][3*j+1] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_NorthEastSouth:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					break;
				}
				case ERoom_NorthEastWest:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_NorthSouthWest:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_EastSouthWest:
				{
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					m_cellMap[3*i+1][3*j] = 1;
					break;
				}
				case ERoom_Unknown:
				{
					m_cellMap[3*i][3*j]     = 0;
					m_cellMap[3*i+2][3*j]   = 0;
					m_cellMap[3*i][3*j+2]   = 0;
					m_cellMap[3*i+2][3*j+2] = 0;
					m_cellMap[3*i+1][3*j+1] = -1;
					m_cellMap[3*i][3*j+1]   = -1;
					m_cellMap[3*i+1][3*j+2] = -1;
					m_cellMap[3*i+2][3*j+1] = -1;
					m_cellMap[3*i+1][3*j]   = -1;
					break;
				}
			}

		} // for cols
	} // for rows
}

void CMap::SetCurrentRoomType(ERoom roomType)
{	
	m_roomMap[m_nextRoom[0]][m_nextRoom[1]] = roomType;
	UpdateCellMap();
}

void CMap::CalculateBlockRooms(vector<int>* pBlockRooms) const
{
	DEBUG_METHOD();
	pBlockRooms->clear();

	for(int i=1; i<m_cellwidth; i+=3)
	{
		for(int j=1; j<m_cellheight; j+=3)
		{
			if(m_cellMap[i][j] ==2)
			{
				pBlockRooms->push_back((((i-1)*m_cellwidth)/3) + (j-1)/3);
			}
		}
	}
}

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function computes a the indices of the vertices bordering a room.
 * WARNING: It does not check whether the vertices actually exist!
 *
 * INPUTS (overload 1):
 * room_index - The index of the room in the linear room indexing.
 *
 * INPUTS (overload 2):
 * row - The row index of the room
 * col - The column index of the room
 *
 * INPUTS (overload 3 - private):
 * coord - A two element vector containing the row index, followed by the column index.
 *
 * RETURN VALUE:
 * A 4-element vector of integers representing the indices of the vertices which could border the
 * room (no check is performed to ensure that the vertices exist!)
 * The vertices are returned in the order North, East, South, West.
 *
 */
vector<int> CMap::CalculateRoomVertices(int room_index) const
{
	DEBUG_METHOD();
	vector<int> coord = RoomIndextoCoord(room_index);
	return CalculateRoomVertices(coord);
}

vector<int> CMap::CalculateRoomVertices(int row, int col) const
{
	DEBUG_METHOD();
	vector<int> coord { row, col };
	return CalculateRoomVertices(coord);
}

vector<int> CMap::CalculateRoomVertices(vector<int> coord) const
{
	DEBUG_METHOD();
	vector<int> roomVertices;

	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1] +1);  // North
	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1] +2);  // East
	roomVertices.push_back((coord[0]+1)*(2*(m_cellwidth/3)+1) +2*coord[1]); // South
	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1]);     // West

	return roomVertices;
}

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function calculates coordinates for a given vertex.
 *
 * The coordinate of a vertex is derived from the (row,column) 'coordinates' in the room map.
 *
 * The vertex above a room has the same row as that room.
 * It will necessarily be in the middle of the room as far as columns are concerned, and is given
 * column index 0.5 greater than its adjacent rooms.
 *
 * The vertex to the left of a room has the same column as that room.
 * It will necessarily be in the middle of the room as far as rows are concerned, and is given row
 * index 0.5 greater than its adjacent rooms.
 *
 * INPUTS:
 * vertex - The vertex linear index. This MUST be non-negative (since the C++ integer arithmetic
 * 	doesn't do what you'd expect for negative numbers!)
 *
 * RETURNS:
 * A two element vector containing the row and column indices of the vector (in that order).
 *
 */
vector<double> CMap::CalculateVertexCoords(int vertex) const
{
	DEBUG_METHOD();

	int roomWidth = m_cellwidth / 3;

	double row = floor(vertex / (2*roomWidth+1));
	double col = ( vertex % (2*roomWidth+1) ) / 2.0;

	row += 0.5 * ( 1 - (vertex % (2*roomWidth+1)) % 2 );

	return vector<double> { row, col };
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// This functions take a Room Enum and returns the vertices of the room in a vector with 1 for vertex
// 0 for no vertex and -1 for unknown. The order of the vertices in the vector is
// North East South West.
vector<int> CMap::GetRoomVertices(ERoom room_type)
{
	DEBUG_METHOD();

	vector<int> vertex_flag;

	switch (room_type)
	{
	case ERoom_Empty:
	{
		vertex_flag = {0, 0, 0, 0};
		break;
	}
	case ERoom_Cross:
	{
		vertex_flag = {1, 1, 1, 1};
		break;
	}
	case ERoom_North:
	{
		vertex_flag = {1, 0, 0, 0};
		break;
	}
	case ERoom_East:
	{
		vertex_flag = {0, 1, 0, 0};
		break;
	}
	case ERoom_South:
	{
		vertex_flag = {0, 0, 1, 0};
		break;
	}
	case ERoom_West:
	{
		vertex_flag = {0, 0, 0, 1};
		break;
	}
	case ERoom_NorthEast:
	{
		vertex_flag = {1, 1, 0, 0};
		break;
	}
	case ERoom_NorthSouth:
	{
		vertex_flag = {1, 0, 1, 0};
		break;
	}
	case ERoom_NorthWest:
	{
		vertex_flag = {1, 0, 0, 1};
		break;
	}
	case ERoom_EastSouth:
	{
		vertex_flag = {0, 1, 1, 0};
		break;
	}
	case ERoom_EastWest:
	{
		vertex_flag = {0, 1, 0, 1};
		break;
	}
	case ERoom_SouthWest:
	{
		vertex_flag = {0, 0, 1, 1};
		break;
	}
	case ERoom_NorthEastSouth:
	{
		vertex_flag = {1, 1, 1, 0};
		break;
	}
	case ERoom_NorthEastWest:
	{
		vertex_flag = {1, 1, 0, 1};
		break;
	}
	case ERoom_NorthSouthWest:
	{
		vertex_flag = {1, 0, 1, 1};
		break;
	}
	case ERoom_EastSouthWest:
	{
		vertex_flag = {0, 1, 1, 1};
		break;
	}
	case ERoom_Unknown:
		vertex_flag = {-1, -1, -1, -1};
	}


	return vertex_flag;
}

int CMap::GetEntranceVertex() const
{
	DEBUG_METHOD();

	vector<int> coord = {m_cellheight/3, 0};

	return (coord[0]+1)*(2*m_cellwidth/3+1) + 2*coord[1] +1;
}

int CMap::GetExitVertex() const
{
	DEBUG_METHOD();

	vector<int> coord = {0, m_cellwidth/3};

	return (coord[0])*(2*m_cellwidth/3 + 1) + 2*coord[1] + 1;
}

int CMap::GetCurrentVertex() const
{
	DEBUG_METHOD();

	return m_currentVertex;
}

// This returns the room we are about to enter while following instructions
std::vector<int> CMap::GetNextRoom() const
{
	DEBUG_METHOD();
	return m_nextRoom;
}

void CMap::SetNextRoom(int new_room_index) // TODO: Unnecessary?
{
	DEBUG_METHOD();

	std::vector<int> coord = RoomIndextoCoord(new_room_index);

	m_nextRoom.resize(2);
	m_nextRoom[0] = coord[0];
	m_nextRoom[1] = coord[1];
}

void CMap::SetNextRoom(int row, int col) // TODO: Unnecessary?
{
	DEBUG_METHOD();

	m_nextRoom.resize(2);
	m_nextRoom[0] = row;
	m_nextRoom[1] = col;
}


void CMap::SetCurrentVertex(int new_vertex_index)
{
	DEBUG_METHOD();
	m_currentVertex = new_vertex_index;
}

vector<int> CMap::RoomIndextoCoord(int room_index) const
{
	DEBUG_METHOD();

	int row_index = room_index/(2*m_cellwidth +1);
	int col_index = room_index % (2*m_cellwidth +1);

	vector<int> roomCoord = {row_index, col_index};
	return roomCoord;
}


void CMap::FollowInstructions(CInstructions &inputInstructions)
{
	DEBUG_METHOD();

	//int current_vertex = GetCurrentVertex(); // Why use this when we are a member function of CMap??

	// Extract information from inputInstructions
	vector<EInstruction> instructionList = inputInstructions.GetInstructions();
	vector<ERoom> roomList = inputInstructions.GetRoomList();
	vector<EOrientation> orientationList = inputInstructions.GetOrientations();
	vector<int> vertexList = inputInstructions.GetVertexList();

	// Check m_currentVertex is valid
	if (m_currentVertex != instructionList[0]) CSignals::Error();

	// Move and update location member variables as you go
	for (int i = 0; i < instructionList.size(); i++)
	{
		CManouvre::InstructionToManouvre(instructionList[i]);

		m_currentVertex = vertexList[i+1];
		m_currentOrientation = orientationList[i+1];

		switch (orientationList[i])
		{
			case EOrientation_North:
				m_nextRoom[0] -= 1;
				break;
			case EOrientation_East:
				m_nextRoom[1] += 1;
				break;
			case EOrientation_South:
				m_nextRoom[0] += 1;
				break;
			case EOrientation_West:
				m_nextRoom[1] -= 1;
				break;
		}
	}

}

EInstruction CMap::FollowInstructionsNotLast(CInstructions & inputInstructions)
{
	DEBUG_METHOD();

	//int current_vertex = GetCurrentVertex();

	vector<EInstruction> instructionList = inputInstructions.GetInstructions();
	vector<ERoom> roomList = inputInstructions.GetRoomList();
	vector<EOrientation> orientationList = inputInstructions.GetOrientations();
	vector<int> vertexList = inputInstructions.GetVertexList();

	if (m_currentVertex != instructionList[0]) CSignals::Error();

	for (int i = 0; i < instructionList.size()-1; i++)
	{
		CManouvre::InstructionToManouvre(instructionList[i]);

		m_currentVertex = vertexList[i+1];
		m_currentOrientation = orientationList[i+1];

		switch (orientationList[i+1])
		{
			case EOrientation_North:
				m_nextRoom[0] -= 1;
				break;
			case EOrientation_East:
				m_nextRoom[1] += 1;
				break;
			case EOrientation_South:
				m_nextRoom[0] += 1;
				break;
			case EOrientation_West:
				m_nextRoom[1] -= 1;
				break;
		}
	}

	return instructionList[instructionList.size()-1];
}

void CMap::populateDistanceMatrixFromArray(std::vector<int> roomVertices, int rowCoordinate, int columnCoordinate, int roomWidth)
{
	DEBUG_METHOD();

	int n = roomWidth;

	// x = i(2n + 1) + 2j
	// y = x + 2n + 2


	int i_coordinate = rowCoordinate;
	int j_coordinate = columnCoordinate;

	int vertexA_Coordinate = 0, vertexB_Coordinate = 0;
	int edge_Magnitude;

	int firstVertexOfRoom = i_coordinate * ((2 * n) + 1) + 2 * j_coordinate;

	int NorthVertexCoordinate = firstVertexOfRoom + 1;
	int EastVertexCoordinate = firstVertexOfRoom + 2;

	
	int SouthVertexCoordinate = firstVertexOfRoom + (2 * n) + 2;

	int WestVertexCoordinate = firstVertexOfRoom;

	int convertedVertexArray[4] = { NorthVertexCoordinate, EastVertexCoordinate, SouthVertexCoordinate, WestVertexCoordinate };

	// Main body of function:

	for (int i = 0; i < 4; i++)
	{
		if (roomVertices.at(i) != 0)
		{
			// if != 0, the a coordinate is convertedVertexArray[i]

			vertexA_Coordinate = convertedVertexArray[i];

			// loop through the rest of the integers in the array to see if any of them are non-zero
			for (int j = i + 1; j < 4; j++) {

				// if there is another non-zero value, the b coordinate is convertedVertexArray[j]
				if (roomVertices.at(j) != 0) {
					vertexB_Coordinate = convertedVertexArray[j];

					// coordinates are only added if both vertices are non-zero
					if (j == i + 1 || j == i + 3) {
						edge_Magnitude = CORNER_PATH_WEIGHT;
					}
					else if (j == i + 2) {
						edge_Magnitude = STRAIGHT_PATH_WEIGHT;
}
					else { edge_Magnitude = -1; }


					// Add two entries to distance matrix.

					m_distanceMatrix.at(vertexB_Coordinate).at(vertexA_Coordinate) = edge_Magnitude;
					m_distanceMatrix.at(vertexA_Coordinate).at(vertexB_Coordinate) = edge_Magnitude;
				
				}
			}
		}
	}
}

void CMap::WriteCellMap(string filepath)
{
	DEBUG_METHOD();

	CParseCSV::WriteCSV(m_cellMap, filepath);
}

vector<vector<double>> CMap::DistanceMatrix()
{
	DEBUG_METHOD();

	// x = i(2n + 2j) 
	// y = x + 2n + 2

	int westPoint, southPoint, roomWidth;
	roomWidth = m_cellwidth/3;

	int n = roomWidth;

	// Calculate the total number of vertices.

	int distanceMatrixSize = n*(n + 1) + (n + 1)*(n + 1);

	m_distanceMatrix.clear();

	m_distanceMatrix.resize(distanceMatrixSize);

	// Change resize vectors and populate with -1.
	
	for (int i = 0; i < distanceMatrixSize; i++) 
	{
		m_distanceMatrix[i].resize(distanceMatrixSize, -1.0);
	}


	///////////////////////////////////////////////////////////////////
	//  Check which rooms contain blocks

	std::vector<int> blockRooms;
	CalculateBlockRooms(&blockRooms);
	std::vector<std::vector<int>> blockRoomCoords;

	blockRoomCoords.resize(blockRooms.size());

	///////////////////////////////////////////////////////////////////
	// Convert to coordinates of room

	for (int i = 0; i < blockRooms.size(); i++) {
		blockRoomCoords.at(i) = RoomIndextoCoord(blockRooms.at(i));
	}


	for (int i = 0; i < roomWidth; i++)
	{
		for (int j = 0; j < roomWidth; j++)
		{
			bool isBlockRoom = false;
			// cycle through BlockRoomCoords and check if the current room contains a block
			for (int k = 0; k < blockRooms.size(); k++) {
				if (blockRoomCoords.at(k).at(0) == i && blockRoomCoords.at(k).at(1) == j) {
					isBlockRoom = true;
					break;
				}
			}
			if (!isBlockRoom) {
				ERoom room_type = m_roomMap.at(i).at(j);
				populateDistanceMatrixFromArray(GetRoomVertices(room_type), i, j, roomWidth);
			}
		}
	}

	return m_distanceMatrix;
}

std::vector<std::vector<double>> CMap::GetDistanceMatrix()
{
	DEBUG_METHOD();

	return m_distanceMatrix;
}




