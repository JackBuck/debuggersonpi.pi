////////////////////////////////////////////////////////////////////////////////////////////////////
// EnumsHeader.h
// Created: 15/11/15
// Author: Hannah Howell
//

// This header contains all the enums that are needed across multiple classes.

#ifndef SRC_ENUMS_H_
#define SRC_ENUMS_H_


// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const double HALFROOMLENGTH = 1.0;
const double ROOMLENGTH = 2.0;
const double DISTANCE_TO_FIRST_CELL = ROOMLENGTH / 3;

const double STRAIGHT_PATH_WEIGHT = 1.0;
const double CORNER_PATH_WEIGHT = 2.0;

const int UNKNOWN_TEST_RESULT=0;


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
	ERoom_West,
	ERoom_Unknown
};

enum EInstruction
{
	EInstruction_Stop,
	EInstruction_Start,
	EInstruction_Straight,
	EInstruction_TurnLeft,
	EInstruction_TurnRight,
	EInstruction_Invalid
};


enum EOrientation
{
	EOrientation_North,
	EOrientation_East,
	EOrientation_South,
	EOrientation_West
};



#endif /* SRC_ENUMS_H_ */
