////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "CMap.h"
#include<iostream>
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

	for(int height_index=0; height_index < room_height; height_index++)
	{ 
		for(int width_index=0; width_index< room_width; width_index++)
		{
			vector<bool> room_flag;
			room_flag.assign(16, true);

			if(m_map[3*height_index][(3*width_index)+1] == 0)
			{ 
				room_flag[Cross] = false;
				room_flag[NorthEast] = false;
				room_flag[NorthSouth] = false;
				room_flag[NorthWest] = false;
				room_flag[NorthEastSouth] = false;
				room_flag[NorthSouthWest] = false;
				room_flag[North] = false;
			}


			if (m_map[3 * height_index+1][(3 * width_index)] == 0)
			{
				room_flag[EastWest] = false;
				room_flag[EastSouthWest] = false;;
				room_flag[SouthWest] = false;
				room_flag[SouthWest] = false;
				room_flag[West] = false;
			}

			if (m_map[3 * height_index + 1][(3 * width_index)] == 0)
			{
				room_flag[EastWest] = false;
				room_flag[EastSouthWest] = false;;
				room_flag[SouthWest] = false;
				room_flag[SouthWest] = false;
				room_flag[West] = false;
			}

			if (m_map[3 * height_index + 1][(3 * width_index)+2] == 0)
			{
				room_flag[East] = false;
				room_flag[EastSouth] = false;;
			}

			if (m_map[3 * height_index + 2][(3 * width_index) + 1] == 0)
			{
				room_flag[South] = false;
			}

			int count = 0;

			for(int i=0; i<16; i++)
			{
				if(room_flag[i])
				{
					count++;
					int temp_room = static_cast<room_type>( i );

					if (width_index == 0)
					{
						vector<int> temp_vec;
						temp_vec.push_back(temp_room);
						m_roomMap.push_back(temp_vec);
					}
					else
					{
						m_roomMap[height_index].push_back(temp_room);
					}
					


					////////////////////////////////////////////////////////////////////////////////
					// Temporary Check

					cout << temp_room;
				}
			}
			cout << endl;
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



