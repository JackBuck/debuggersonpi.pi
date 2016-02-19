////////////////////////////////////////////////////////////////////////////////////////////////////
// Manouvre.h
// Created: 03/02/16
// Author: Hannah Howell
//

// This is a place holder for the manouvre class and has been created so that the functions can be used 
// the functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.


#ifndef SRC_CManouvre_H_
#define SRC_CManouvre_H_

//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Instructions.h"

//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CManouvre
{

	// === Public Functions =========================================================================
public:

	static void InstructionToManouvre(EInstruction instruction_type);

	static void MoveToStartVertex();
	static void ExitMap();
	static int ApproachAndPhotographBlock();
	static void CollectBlock();
	static void ReleaseBlock();
	static void ReverseAndUTurn();

	static void StraightAcrossRoom();
	static void TurnLeftInRoom();
	static void TurnRightInRoom();
	static ERoom MoveForwardAndDetectRoomType();
};


#endif /* SRC_CChallenges_H_ */

