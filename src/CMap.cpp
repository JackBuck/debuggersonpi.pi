////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "CMap.h"
#include "Signals.h"
#include "Manouvre.h"
#include<iostream>
#include<fstream>
#include "EnumsHeader.h"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int ENTRANCEPORCHROOM = -1;

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is a constructor for the CMap Class. It takes the filepath of the raw input data
// and from this creates an instance of the class.
CMap::CMap(string filepath)
{
	ifstream myReadFile;
	myReadFile.open(filepath);


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Check file has been correctly opened

	if (myReadFile.is_open())
	{
		myReadFile >> m_cellwidth >> m_cellheight;

		for(int i=0; i<m_cellheight; i++)
		{ 

			/////////////////////////////////////////////////////////////////////////////////////
			// Add new vector for new row of map

			int temp_int;
			vector<int> temp_vec;
			myReadFile >> temp_int;
			temp_vec.push_back(temp_int);
			m_cellMap.push_back(temp_vec);

			

			for(int j=1; j<m_cellwidth; j++)
			{
				/////////////////////////////////////////////////////////////////////////////////////
				// Fill row of array

				myReadFile >> temp_int;
				m_cellMap[i].push_back(temp_int);
			}
		}
	}
	else
	{
		CSignals::Error();
		cout << "unable to open file"; // EXCEPTION - eventually this will need to throw a proper exception
	}

	CreateRoomMap();
	ComputeCellMapSize();

	//////////////////////////////////////////////////////////////////////////////////////
	// Entrance and exit predefined

	m_firstRoom = m_cellheight*m_cellwidth;
	m_exitRoom = m_cellwidth-1;

	m_entranceCell = {3*m_firstRoom , 2};
	m_exitCell = {2, 3*m_cellwidth};

	//////////////////////////////////////////////////////////////////////////////////////
	// Assume positioned at start.

	m_currentVertex = GetEntranceVertex();

	///////////////////////////////////////////////////////////////////////////////////////
	// Current room is entrance room which is not defined in our map so set to 
	m_currentRoom = ENTRANCEPORCHROOM;
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialiser for unknown map.
CMap::CMap(int room_height, int room_width)
{
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
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function creates the room map from a cell map.
void CMap::CreateRoomMap()
{

	int room_height = m_cellheight/3;
	int room_width = m_cellwidth/3;

	for(int height_index=0; height_index<room_height; height_index++)
	{ 
		for(int width_index=0; width_index<room_width; width_index++)
		{
			//////////////////////////////////////////////////////////
			// Determine room type

			vector<bool> room_flag;
			room_flag.assign(16, true);

			if(m_cellMap[(3*height_index)][(3*width_index) + 1] == 0)
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

			if (m_cellMap[(3*height_index) + 1][(3*width_index) + 2] == 0)
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

			if (m_cellMap[(3 * height_index) + 2][(3 * width_index) + 1] == 0)
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
			
			if (m_cellMap[(3*height_index) + 1][(3*width_index)] == 0)
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
	m_cellheight= m_cellMap.size();
	if(m_cellheight > 0)	m_cellwidth = m_cellMap[0].size();
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<vector<ERoom>> CMap::GetRoomMap()
{
	return m_roomMap;
}

ERoom CMap::GetRoomType(int room_index)
{
	int row_index;
	return ERoom();
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<vector<int>> CMap::GetCellMap()
{
	return m_cellMap;
}

int CMap::GetEntranceRoom()
{
	return m_firstRoom;
}

int CMap::GetExitRoom()
{
	return m_exitRoom;
}

std::vector<int> CMap::GetEntranceCell()
{
	return m_entranceCell;
}

std::vector<int> CMap::GetExitCell()
{
	return m_exitCell;
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CMap::UpdateRoomMap()
{
	CreateRoomMap();
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CMap::UpdateCellMap()
{
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
			m_cellMap[3*i][3*j] = 0;
			m_cellMap[3*i+2][3*j] = 0;
			m_cellMap[3*i][3 * j+2] = 0;
			m_cellMap[3*i+2][3 * j+2] = 0;
			m_cellMap[3*i+1][3 * j+1] = 1;


			switch (m_roomMap[i][j])
			{
				case ERoom_Empty:
				{
					m_cellMap[3 * i + 1][3*j + 1] = 0;
					break;
				}
				case ERoom_Cross:
				{
					m_cellMap[3*i][3*j+1] = 1;
					m_cellMap[3*i+1][3*j+2] = 1;
					m_cellMap[3*i+2][3*j+1] = 1;
					m_cellMap[3*i + 1][3*j] = 1;
					break;
				}
				case ERoom_North:
				{
					m_cellMap[3*i][3*j + 1] = 1;
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
			}

			for (unsigned int i = 0; i<m_cellMap.size(); i++)
			{
				for (unsigned int j = 0; j<m_cellMap[i].size(); j++)
				{
					std::cout << m_cellMap[i][j];
				}
				std::cout << std::endl;
				
			}
			std::cout << std::endl;
		}
	}
}
void CMap::CalculateBlockRooms(std::vector<int>* pBlockRooms)
{
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

std::vector<int>  CMap::CalculateRoomVertices(int room_index)
{
	std::vector<int> roomVertices;


	std::vector<int> coord = RoomIndextoCoord(room_index);

	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1]);
	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1] +1);
	roomVertices.push_back(coord[0]*(2*(m_cellwidth/3)+1) +2*coord[1] +2);
	roomVertices.push_back((coord[0]+1)*(2*(m_cellwidth/3)+1) +2*coord[1]);

	return roomVertices;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// This functions take a Room Enum and returns the vertices of the room in a vector with 1 for vertex
// 0 for no vertex and -1 for unknown. The order of the vertices in the vector is
// North East South West.
std::vector<int> CMap::GetRoomVertices(ERoom room_type)
{
	std::vector<int> vertex_flag;

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

int CMap::GetEntranceVertex()
{
	std::vector<int> coord = {m_cellwidth/3, 0};

	return (coord[0]+1)*(2*m_cellwidth+1) + 2*coord[1] +1;
}

int CMap::GetExitVertex()
{
	std::vector<int> coord = {0, m_cellwidth/3};

	return (coord[0])*(2*m_cellwidth+1) + 2*coord[1] +2;
}

int CMap::GetCurrentVertex()
{
	return m_currentVertex;
}

int CMap::GetCurrentRoom()
{
	return m_currentRoom;
}

int CMap::SetCurrentVertex(int new_vertex)
{
	return 0;
}

std::vector<int> CMap::RoomIndextoCoord(int room_index)
{
	int row_index = room_index/(2*m_cellwidth +1);
	int col_index = room_index % (2*m_cellwidth +1);

	std::vector<int> roomCoord = {row_index, col_index};
	return roomCoord;
}


void CMap::FollowInstructions(CInstructions &inputInstructions)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// Check we are at start vertex.

	int current_vertex = GetCurrentVertex();

	std::vector<EInstruction> instructionList = inputInstructions.GetInstructions();
	std::vector<ERoom> roomList = inputInstructions.GetRoom();
	std::vector<EOrientation> oreintationList = inputInstructions.GetOrientation();

	if(current_vertex != instructionList[0]) CSignals::Error();

	for(int i=0; i<instructionList.size(); i++)
	{
		CManouvre::InstructionToManouvre(instructionList[i]);

		
	}


}


