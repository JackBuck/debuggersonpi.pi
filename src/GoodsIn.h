////////////////////////////////////////////////////////////////////////////////////////////////////
// GoodsIn.h
// Created: 28/11/15
// Author: Hannah Howell
//

// This is a place holder for the GoodsIn class and has been created so that the functions can be used.
// The functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.


#ifndef SRC_CGoodsIn_H_
#define SRC_CGoodsIn_H_

//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "EnumsHeader.h"


//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CGoodsIn
{
	// === Public Functions =========================================================================
public:
	static void Forward(double distance, bool watch_sensors);
	static void Reverse(double distance, bool watch_sensors);
	static void TurnLeft90();
	static void TurnRight90();
	static void Stop();

	static ERoom GetCurrentRoomType();



	// === Private Functions ========================================================================
};


#endif SRC_CChallenges_H_
