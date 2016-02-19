////////////////////////////////////////////////////////////////////////////////////////////////////
// CInstructions.cpp
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
#include "Instructions.h"


// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This function is a constructor for the CInstructor Class. It takes a reference to the raw input data
// and from this creates an instance of the class.

CInstructions::CInstructions(const std::vector<int> &vertexList, const int map_width)
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// This vector contains the list of rooms that will be moved through during each instruction.

	m_roomList.clear();
	m_roomList.reserve(vertexList.size()-1);


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// This vector contains the list of the orientation of the robot BETWEEN each instruction.
	// Note this has one more entry than the instruction list.

	m_orientationBetweenInstructions.clear();
	m_orientationBetweenInstructions.reserve(vertexList.size());
	EOrientation current_orientation;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// This vector contains the instructions to move between vertices.
	m_instructions.resize(vertexList.size()-1);



	///////////////////////////////////////////////////////////////////////////////////////////////////
	// The difference between the first two vertex labels tells us the orientation the robot should be
	// in at the start to be facing the correct way.
	int num_diff = vertexList[1] - vertexList[0];
	double level_check = vertexList[0]/2*map_width;
	
	if(num_diff == 1)
	{ 
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// If the difference is 1 there are two options moving from West to North (going East) or North to East
		// (going South) we can distinguish between the two by checking if the the first is even.

		if((static_cast<int>(floor(level_check)) %2) == vertexList[0] % 2) current_orientation = EOrientation_East;
		else current_orientation = EOrientation_South;
	}
	else if(num_diff == -1)
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// If the difference is -1 there are two options are opposite moving from North to West 
		// (South) or East to North (West) we can distinguish between the two by checking if the the first is even.

		if((static_cast<int>(floor(level_check)) %2) == vertexList[0] % 2) current_orientation = EOrientation_West;
		else current_orientation = EOrientation_South;
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// The other orientations are calculated in a similar manner. 
	
	else if(num_diff ==  2)					current_orientation = EOrientation_East;

	else if(num_diff == -2)					current_orientation = EOrientation_West;

	else if(num_diff ==  2*(map_width +1))	current_orientation = EOrientation_South;

	else if(num_diff == -2*(map_width+1))	current_orientation = EOrientation_North;

	else if(num_diff == 2*map_width)		current_orientation = EOrientation_West;

	else if(num_diff ==  2*map_width)		current_orientation = EOrientation_North;

	else if(num_diff ==  2*map_width +2)	current_orientation = EOrientation_East;

	else if(num_diff ==  -(2*map_width +2))	current_orientation = EOrientation_North;


	/////////////////////////////////////////////////////////////////////////////////////////////
	// Populate orientation vector with start orientation.
	m_orientationBetweenInstructions[0] = current_orientation;


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Similarly to the way we worked out the initial orientation we can compare the vertex labels
	// of the vertices we enter and leave the room through. Because we have a specific labelling
	// system the difference between the two labels give us there position relative to each other.


	//					i(2n+1) +2j +1
	//					 _ _ _
	//					|_ _ _|
	//		i(2n+1) +2j	|_ _ _|		i(2n+1) + 2j + 2
	//					|_ _ _|
	//
	//					(i+1)(2n+1) + 2j + 1
	//

	for(size_t i=0; i<vertexList.size()-1; i++)
	{	
		num_diff = vertexList[i+1] - vertexList[i];
		EInstruction current_instruction;

		if(num_diff == 1)
		{	
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Either W to N or N to E, both are left turns
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else if(num_diff == -1)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Either N to W or E to N, both are right turns
			current_instruction = EInstruction_TurnRight;
			break;
		}
		else if(num_diff == 2)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			//  W to E straight.
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == -2)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Either E to W straight
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == 2*(map_width +1))
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// N to S straight
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == -2*(map_width+1))
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// S to N straight
			current_instruction = EInstruction_Straight;
			break;
		}
		else if(num_diff == 2*map_width)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// E to S turn left
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else if(num_diff == 2*map_width)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// S to E turn right
			current_instruction = EInstruction_TurnRight;
			break;
		}
		else if(num_diff == 2*map_width + 2)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// W to S turn right
			current_instruction = EInstruction_TurnRight;
			break;
		}

		else if(num_diff == -2*map_width - 2)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// S to W turn left
			current_instruction = EInstruction_TurnLeft;
			break;
		}
		else
		{
			///////////////////////////////
			// TODO throw exception.
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
		// Compute new orientation
	
	
		if(current_instruction == EInstruction_TurnLeft)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Rotate orientation anti clockwise
			current_orientation = static_cast<EOrientation>((current_orientation +1) %4);
		}
		else if(current_instruction == EInstruction_TurnRight)
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// Rotate orientation clockwise
			current_orientation = static_cast<EOrientation>((current_orientation -1) %4);
		}

		/////////////////////////////////////////////////////////////////////////////
		// If the instruction is straight the orientation doesnt change.

		m_orientationBetweenInstructions[i+1] = current_orientation;



		/////////////////////////////////////////////////////////////////////////////
		// Compute room the instruction moves through. The easiest way to do this is 
		// to look at the orientation of the robot as this tells you which vertex it 
		// relative to the room. (N S E or W) from this we can use the equations above
		// to find the row and column of the current room.
		//
		// The number row is calculating by finding the number of complete rows each
		// using (2n+1) vertices before this vertex. floor(vertex label/(2n+1))
		// The column is found by looking the remainder when the complete rows are removed
		// vertex label mod (2n+1).

		int row_index;
		int col_index;


		//////////////////////////////////////////////////////////////////////////////////////////////
		// If the remainder after the rows is even we know we are at a vertex on a vertical line i.e. 
		// an E or W vertex. We can then tell by our orientation which we are at
		if(static_cast<int>(floor(vertexList[i]/(2*map_width+1)))  %2)
		{
			row_index = static_cast<int> (floor(vertexList[i]/(2*map_width+1)));

			if(current_orientation == EOrientation_East)
			{
				col_index = static_cast<int> ((vertexList[i] % (2*map_width+1))/2 -1);
			}
			else if(current_orientation == EOrientation_West)
			{
				col_index = static_cast<int> ((vertexList[i] %(2*map_width+1) -1))/2;	
			}
		}
		else
		{

			/////////////////////////////////////////////////////////////////////////////////////////
			// We are on a horizontal vertex e.g. N or S

			if(current_orientation == EOrientation_North)
			{
				row_index = static_cast<int>(floor(vertexList[i]/2*map_width));
				col_index = (vertexList[i] %(2*map_width+1) -1)/2;	
			}
			else if(current_orientation == EOrientation_South)
			{
				////////////////////////////////////////////////////////////////////////////////
				// Note here we have a different row calculation.

				row_index = static_cast<int>(floor(vertexList[i]/2*map_width)) -1;
				col_index = (vertexList[i] %(2*map_width+1) -1)/2;	
			}
		}

		m_roomList[i] = static_cast<ERoom>(row_index*map_width + col_index);

		m_instructions[i] = current_instruction;
	}
}


std::vector<EInstruction> CInstructions::GetInstructions()
{
	return m_instructions;
}

std::vector<ERoom> CInstructions::GetRoomList()
{
	return m_roomList;
}

std::vector<EOrientation> CInstructions::GetOrientations()
{
	return m_orientationBetweenInstructions;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// This function truncates instructions if they go through the room of interest.
void CInstructions::TruncateAtRoom(int room_index)
{
	for(size_t i=0; i<m_instructions.size(); i++)
	{
		if(m_roomList[i] == room_index)
		{
			m_instructions.resize(i-1);
			m_roomList.resize(i-1);
			m_orientationBetweenInstructions.resize(i);
		}
	}
}



