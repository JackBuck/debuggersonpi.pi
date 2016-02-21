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







//////////////////////////////////////////////////////////////////////////////////////////
//
void CManouvre::InstructionToManouvre(EInstruction instruction_type)
{
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

//////////////////////////////////////////////////////////////////////////////////////////
// Move into the maze to entrance vertex (edge of first room).
void CManouvre::MoveToStartVertex()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
// Move out of map from exit vertex.
void CManouvre::ExitMap()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
// Move straight across a room from one vertex to another.
void CManouvre::StraightAcrossRoom()
{
	CGoodsOut::Forward(ROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnLeftInRoom()
{
	CGoodsOut::Forward(HALFROOMLENGTH, true);
	CGoodsOut::TurnLeft90();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Move across the room from vertex to another by turning left
void CManouvre::TurnRightInRoom()
{
	CGoodsOut::Forward(HALFROOMLENGTH, true);
	CGoodsOut::TurnRight90();
	CGoodsOut::Forward(HALFROOMLENGTH, false);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Move forward into room to junction. Detect junction and return room type Enum.
ERoom CManouvre::MoveForwardAndDetectRoomType()
{

	return ERoom_Empty;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Approach a block from vertex of room and take photograph and return block number.
int CManouvre::ApproachAndPhotographBlock()
{
	return 0;
}



///////////////////////////////////////////////////////////////////////////////////////
// Move arm to collect block and move forward to vertex.
void CManouvre::CollectBlock()
{

}



///////////////////////////////////////////////////////////////////////////////////////
// Move arm to release block
void CManouvre::ReleaseBlock()
{
}

//////////////////////////////////////////////////////////////////////////////////////
// Reverse the robot away from a block and u turn. (Be careful of block!) 
// This may also be used when there carrying the block.
void CManouvre::ReverseAndUTurn()
{

}


