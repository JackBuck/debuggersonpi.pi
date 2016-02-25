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
#include "EnumsHeader.h"


//////////////////////////////////////////////////////////////////////////////////////////
//
void CManouvre::InstructionToManouvre(EInstruction instruction_type)
{
	DEBUG_METHOD();

	switch(instruction_type)
	{
	case EInstruction_Straight:
	{
		CManouvre::StraightAcrossRoom();
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

void CManouvre::LastInstructionBeforeBlock(EInstruction instruction_type)
{
	DEBUG_METHOD();

	switch (instruction_type)
	{
	case EInstruction_Straight:
	{
		CManouvre::StraightAcrossRoom();
	}
	case EInstruction_TurnLeft:
	{
		CManouvre::TurnRightInRoom();
		CGoodsOut::TurnRight90();
		CGoodsOut::TurnRight90();
		CGoodsOut::Forward(DistanceToFirstCell, false);
	}
	case EInstruction_TurnRight:
	{
		CManouvre::TurnLeftInRoom();
		CGoodsOut::TurnLeft90();
		CGoodsOut::TurnLeft90();
		CGoodsOut::Forward(DistanceToFirstCell, false);
	}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move into the maze to entrance vertex (edge of first room).
void CManouvre::MoveToStartVertex()
{
	DEBUG_METHOD();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move out of map from exit vertex.
void CManouvre::ExitMap()
{
	DEBUG_METHOD();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move straight across a room from one vertex to another.
void CManouvre::StraightAcrossRoom()
{
	DEBUG_METHOD();

	CGoodsOut::Forward(ROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnLeftInRoom()
{
	DEBUG_METHOD();

	CGoodsOut::Forward(HALFROOMLENGTH, true);
	CGoodsOut::TurnLeft90();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnRightInRoom()
{
	DEBUG_METHOD();

	CGoodsOut::Forward(HALFROOMLENGTH, true);
	CGoodsOut::TurnRight90();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Move forward into room to junction. Detect junction and return room type Enum.
ERoom CManouvre::DetectRoomType()
{
	CGoodsIn::GetJunctionType();
	return ERoom_Empty;
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


