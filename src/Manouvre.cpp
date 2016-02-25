////////////////////////////////////////////////////////////////////////////////////////////////////
// Manouvre.cpp
// Created: 15/01/16
// Author: Hannah Howell
//
// This is a place holder for the manouvre class and has been created so that the functions can be used, 
// the functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.


//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Manouvre.h"
#include "GoodsOut.h"
#include "GoodsIn.h"
#include "DebugLog.hpp"


//////////////////////////////////////////////////////////////////////////////////////////
//
void CManouvre::InstructionToManoeuvre(EInstruction instruction_type, ERoom nextRoom)
{
	DEBUG_METHOD();

	switch(instruction_type)
	{
	case EInstruction_Straight:
	{
		if (nextRoom == ERoom_NorthSouth || nextRoom == ERoom_EastWest)
			CManouvre::StraightAcrossRoomNoJunct();
		else
			CManouvre::StraightAcrossRoomJunct();
	}
	case EInstruction_TurnLeft:
	{
		CManouvre::TurnLeftInRoom();
	}
	case EInstruction_TurnRight:
	{
		CManouvre::TurnRightInRoom();
	}
	}

}

void CManouvre::LastInstructionBeforeBlock(EInstruction instruction_type, ERoom nextRoom)
{
	DEBUG_METHOD();

	switch (instruction_type)
	{
	case EInstruction_Straight:
	{
		if (nextRoom == ERoom_NorthSouth || nextRoom == ERoom_EastWest)
			CManouvre::StraightAcrossRoomNoJunct();
		else
			CManouvre::StraightAcrossRoomJunct();
	}
	case EInstruction_TurnLeft:
	{
		CManouvre::TurnRightInRoom();
		CGoodsOut::ForwardDistance(HALFROOMLENGTH, false); // Positions the wheels on the right hand edge of the room
		CGoodsOut::TurnRight90();
		CGoodsOut::TurnRight90();
		CGoodsOut::ForwardDistance(DISTANCE_TO_FIRST_CELL, true);
	}
	case EInstruction_TurnRight:
	{
		CManouvre::TurnLeftInRoom();
		CGoodsOut::ForwardDistance(HALFROOMLENGTH, false); // Positions the wheels on the left hand edge of the room
		CGoodsOut::TurnLeft90();
		CGoodsOut::TurnLeft90();
		CGoodsOut::ForwardDistance(DISTANCE_TO_FIRST_CELL, true);
	}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move into the maze to entrance vertex (edge of first room).
void CManouvre::MoveToStartVertex()
{
	DEBUG_METHOD();
	CGoodsOut::ForwardDistance(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move out of map from exit vertex.
void CManouvre::ExitMap()
{
	DEBUG_METHOD();
	CGoodsOut::ForwardDistance(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move straight across a room from one vertex to another.
void CManouvre::StraightAcrossRoomJunct()
{
	DEBUG_METHOD();

	CGoodsOut::ForwardDetectJunction();
	CGoodsOut::ForwardDetectJunction();
}

void CManouvre::StraightAcrossRoomNoJunct()
{
	DEBUG_METHOD();

	CGoodsOut::ForwardDistance(ROOMLENGTH, true);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnLeftInRoom()
{
	DEBUG_METHOD();

	CGoodsOut::ForwardDetectJunction();
	CGoodsOut::TurnLeft90();

}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnRightInRoom()
{
	DEBUG_METHOD();

	CGoodsOut::ForwardDetectJunction();
	CGoodsOut::TurnRight90();
	
}

/////////////////////////////////////////////////////////////////////////////////////////
// Approach a block from vertex of room and take photograph and return block number.
int CManouvre::ApproachAndPhotographBlock()
{
	DEBUG_METHOD();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Move arm to collect block and move forward to vertex.
void CManouvre::CollectBlock()
{
	DEBUG_METHOD();
}

///////////////////////////////////////////////////////////////////////////////////////
// Move arm to release block
void CManouvre::ReleaseBlock()
{
	DEBUG_METHOD();
}

//////////////////////////////////////////////////////////////////////////////////////
// Reverse the robot away from a block and u turn. (Be careful of block!) 
// This may also be used when there carrying the block.
void CManouvre::ReverseAndUTurn()
{
	DEBUG_METHOD();
	
	CGoodsOut::Reverse(ROOMLENGTH, false);
	CGoodsOut::TurnLeft90();
	CGoodsOut::TurnLeft90();
	CGoodsOut::Reverse(HALFROOMLENGTH, false);
}

ERoom CManouvre::DetectRoomType()
{
	return CGoodsOut::ForwardDetectJunction();
}

