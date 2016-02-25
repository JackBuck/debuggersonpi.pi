////////////////////////////////////////////////////////////////////////////////////////////////////
// GoodsOut.cpp
// Created: 28/11/15
// Author: Hannah Howell
//
// This is a place holder for the GoodsIn class and has been created so that the functions can be used.
// The functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.

#include "GoodsOut.h"
#include "DebugLog.hpp"

void CGoodsOut::Forward(double distance, bool watch_light_sensors)
{
	DEBUG_METHOD();
	int Count = 0;

	// stopCount needs to be set to a number according to the time waited & the time 
	int stopCount;

	// the pic will have to check whether a junction has been detected & when it has, this will become true
	bool junctionDetected = false;

	double currentDistance = 0;

	// checks whether an emergency stop is called many times during a manouvre
	while (ContinueManouvre && Count<stopCount && currentDistance < distance && !junctionDetected)
	{
		// motors move
		// wait a specified time (eg. wait 20ms for 50 stopCount & 1 second total manouvre time)

		// Check light sensors for junction & if so, set junctionDetected to true
		// Check encoders for current distance & increase currentDistance
		// Check for emergency stop

		// If time is a bad thing to go by, ignore the count!
		Count++;
	}
}

void CGoodsOut::Reverse(double distance, bool watch_light_sensors)
{
	DEBUG_METHOD();
	int Count = 0;

	// stopCount needs to be set to a number according to the time waited & the time 
	int stopCount;

	// the pic will have to check whether a junction has been detected & when it has, this will become true
	bool junctionDetected = false;

	double currentDistance = 0;

	// checks whether an emergency stop is called many times during a manouvre
	while (ContinueManouvre && Count<stopCount && currentDistance < distance && !junctionDetected)
	{
		// motors move
		// wait a specified time (eg. wait 20ms for 50 stopCount & 1 second total manouvre time)

		// Check light sensors for junction & if so, set junctionDetected to true
		// Check encoders for current distance & increase currentDistance
		// Check for emergency stop

		// If time is a bad thing to go by, ignore the count!
		Count++;
	}
}

void CGoodsOut::TurnLeft90()
{
	DEBUG_METHOD();
	int Count = 0;

	// stopCount needs to be set to a number according to the time waited & the time 
	int stopCount;

	// should check whether an emergency stop is called many times during a manouvre
	while (ContinueManouvre && Count<stopCount)
	{
		// motors move
		// wait a specified time (eg. wait 20ms for 50 stopCount & 1 second total manouvre time)
		Count++;
	}
}

void CGoodsOut::TurnRight90()
{
	DEBUG_METHOD();
	int Count = 0;

	// stopCount needs to be set to a number according to the time waited & the time 
	int stopCount;

	// should check whether an emergency stop is called many times during a manouvre
	while (ContinueManouvre && Count<stopCount)
	{
		// motors move
		// wait a specified time (eg. wait 20ms for 50 stopCount & 1 second total manouvre time)
		Count++;

		// Check ContinueManouvre
	}
}

void CGoodsOut::Stop()
{
	DEBUG_METHOD();
}

ERoom CGoodsOut::GetCurrentRoomType()
{
	DEBUG_METHOD();
	return ERoom();
}
