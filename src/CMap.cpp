////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "CMap.h"
#include<iostream>%
#include<fstream>


// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;


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
		myReadFile >> m_width >> m_height;

		for(int i=0; i<m_height; i++)
		{ 

			/////////////////////////////////////////////////////////////////////////////////////
			// Add new vector for new row of map

			int temp_int;
			vector<int> temp_vec;
			myReadFile >> temp_int;
			temp_vec.push_back(temp_int);
			m_map.push_back(temp_vec);

			

			for(int j=1; j<m_width; j++)
			{
				/////////////////////////////////////////////////////////////////////////////////////
				// Fill row of array

				myReadFile >> temp_int;
				m_map[i].push_back(temp_int);
			}
		}
	}
	else
	{
		cout << "unable to open file"; // EXCEPTION - eventually this will need to throw a proper exception
	}


	////////////////////////////////////////////////////////////////////////////////////
	// Temporary check

	for (int i=0; i<m_height; i++)
	{
		for (int j=0; j<m_width; j++)
		{
			cout << m_map[i][j];
		}
		cout << endl;
	}

	CreateRoomMap();
	//ComputeMapSize();

	// TODO START AND FINISH DETECTOR
	//m_start = start;
	//m_finish = finish;

	
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is a constructor for the CMap Class, it takes the array of ones and zeros stored in 
// rows, and the room indices of the rooms on the map that are adjacent to the start and finish. 
// It is assumed that the array in of the correct form (i.e. can be subdivided into rooms of 3x3 cells)
CMap::CMap(vector<vector<int>> inputMap, int start, int finish)
{

	m_map = inputMap;
	CreateRoomMap();
	//ComputeMapSize();
	m_start = start;
	m_finish = finish;

}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is incomplete but does compile
void CMap::CreateRoomMap()
{

	int room_height = m_height/3;
	int room_width = m_width/3;

	for(int height_index=0; height_index<room_height; height_index++)
	{ 
		for(int width_index=0; width_index<room_width; width_index++)
		{
			//////////////////////////////////////////////////////////
			// Determine room type

			vector<bool> room_flag;
			room_flag.assign(16, true);

			if(m_map[(3*height_index)][(3*width_index) + 1] == 0)
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

			if (m_map[(3*height_index) + 1][(3*width_index) + 2] == 0)
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

			if (m_map[(3 * height_index) + 2][(3 * width_index) + 1] == 0)
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
			
			if (m_map[(3*height_index) + 1][(3*width_index)] == 0)
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
// Needs checking!
void CMap::ComputeMapSize()
{
	m_height= m_map.size();

	m_width = m_map[0].size();
}


vector<vector<ERoom>> CMap::GetRoomMap()
{
	return m_roomMap;
}



