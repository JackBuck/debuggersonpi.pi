////////////////////////////////////////////////////////////////////////////////////////////////////
// EnumsHeader.h
// Created: 15/11/15
// Author: Hannah Howell
//

// This header contains all the enums that are needed across multiple classes.

#ifndef SRC_ENUMS_H_
#define SRC_ENUMS_H_


// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enum ERoom
{
	ERoom_Empty,
	ERoom_Cross,
	ERoom_NorthSouth,
	ERoom_EastWest,
	ERoom_EastSouthWest,
	ERoom_NorthSouthWest,
	ERoom_NorthEastWest,
	ERoom_NorthEastSouth,
	ERoom_NorthWest,
	ERoom_NorthEast,
	ERoom_EastSouth,
	ERoom_SouthWest,
	ERoom_North,
	ERoom_East,
	ERoom_South,
	ERoom_West
};

enum EInstruction
{
	EInstruction_Stop,
	EInstruction_Start,
	EInstruction_Straight,
	EInstruction_TurnLeft,
	EInstruction_TurnRight,
	EInstruction_LAST
};


enum EOrientation
{
	EOrientation_North,
	EOrientation_East,
	EOrientation_South,
	EOrientation_West
};



#endif SRC_ENUMS_H_
