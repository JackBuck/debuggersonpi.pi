////////////////////////////////////////////////////////////////////////////////////////////////////
// CINstructions.cpp
// Created: 15/01/16
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "EnumsHeader.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<math.h>
#include "CInstructions.h"


// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is a constructor for the CMap Class. It takes the filepath of the raw input data
// and from this creates an instance of the class.

CInstructions::CInstructions(const std::vector<int> &labels, const std::vector<int> &vertexList, const int map_width)
{

	m_roomList.clear();
	m_roomList.reserve(vertexList.size()-1);

	m_orientationBetweenInstructions.clear();
	m_orientationBetweenInstructions.reserve(vertexList.size());
	EOrientation current_orientation;


	m_instructions.resize(vertexList.size()-1);
	EInstruction current_instruction;

	int num_diff = labels[vertexList[1]] - labels[vertexList[0]];
	double level_check = labels[vertexList[0]]/2*map_width;
	
	if(num_diff == 1)
	{
		if((static_cast<int>(floor(level_check)) %2) == labels[vertexList[0] % 2]) current_orientation = EOrientation_East;
		else current_orientation = EOrientation_South;
	}
	else if(num_diff == -1)
	{
		if((static_cast<int>(floor(level_check)) %2) == labels[vertexList[0] % 2]) current_orientation = EOrientation_West;
		else current_orientation = EOrientation_South;
	}
	else if(num_diff ==  2)					current_orientation = EOrientation_East;

	else if(num_diff == -2)					current_orientation = EOrientation_West;

	else if(num_diff ==  2*(map_width +1))	current_orientation = EOrientation_South;

	else if(num_diff == -2*(map_width+1))	current_orientation = EOrientation_North;

	else if(num_diff == 2*map_width)		current_orientation = EOrientation_West;

	else if(num_diff ==  2*map_width)		current_orientation = EOrientation_North;

	else if(num_diff ==  2*map_width +2)	current_orientation = EOrientation_East;

	else if(num_diff ==  -(2*map_width +2))	current_orientation = EOrientation_North;


	m_orientationBetweenInstructions[0] = current_orientation;

	for(int i=0; i<vertexList.size()-1; i++)
	{	
		num_diff = labels[vertexList[i+1]] - labels[vertexList[i]];
		EInstruction current_instruction;

		if(num_diff == 1)
		{
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else if(num_diff == -1)
		{
			current_instruction = EInstruction_TurnRight;
			break;
		}
		else if(num_diff == 2)
		{
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == -2)
		{
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == 2*(map_width +1))
		{
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == -2*(map_width+1))
		{
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == 2*map_width)
		{
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else if(num_diff == 2*map_width)
		{
			current_instruction = EInstruction_TurnRight;
			break;
		}
		else if(num_diff == 2*map_width + 2)
		{
			current_instruction = EInstruction_TurnRight;
			break;
		}

		else if(num_diff == 2*map_width + 2)
		{
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else
		{
			return;
		}
	

		if(current_instruction == EInstruction_TurnLeft)
		{
			current_orientation = static_cast<EOrientation>((current_orientation +1) %4);
		}
		else if(current_instruction == EInstruction_TurnRight)
		{
			current_orientation = static_cast<EOrientation>((current_orientation -1) %4);
		}

		m_orientationBetweenInstructions[i+1] = current_orientation;

		int row_index;
		int col_index;

		if(static_cast<int>(floor(labels[vertexList[i]]/2*map_width))  %2 == (labels[vertexList[i]]) %2)
		{
			if(current_orientation == EOrientation_East)
			{
				row_index = static_cast<int> (floor(labels[vertexList[i]]/2*map_width));
				col_index = static_cast<int> ((labels[vertexList[i]] % (2*map_width))/2 -1);

			}
			else if(current_orientation == EOrientation_West)
			{
				row_index = static_cast<int> (floor(labels[vertexList[i]]/2*map_width));
				col_index = static_cast<int> ((labels[vertexList[i]] %(2*map_width+1) -1))/2;	
			}
		}
		else
		{
			if(current_orientation == EOrientation_North)
			{
				row_index = floor(labels[vertexList[i]]/2*map_width);
				col_index = (labels[vertexList[i]] %(2*map_width+1) -1)/2;	
			}
			else if(current_orientation == EOrientation_South)
			{
				row_index = floor(labels[vertexList[i]]/2*map_width) -1;
				col_index = (labels[vertexList[i]] %(2*map_width+1) -1)/2;	
			}
		}

		m_roomList[i] = static_cast<ERoom>(row_index*map_width + col_index);

		m_instructions[i] = current_instruction;
	}
}


std::vector<EInstruction> CInstructions::GetInstructions()
{
	return std::vector<EInstruction>();
}

std::vector<ERoom> CInstructions::GetRoomList()
{
	return std::vector<ERoom>();
}

std::vector<EOrientation> CInstructions::GetOrientations()
{
	return std::vector<EOrientation>();
}
