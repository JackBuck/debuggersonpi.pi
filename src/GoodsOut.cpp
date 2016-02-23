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
#include "pi_spi.h"
#include "pic_enums.h"

void CGoodsOut::Forward(double distance, bool watch_sensors)
{
	DEBUG_METHOD();

	//Set distance to number of counts (each count = 6mm <> divide by 6)
	distance = distance / 6;

	//move forwards - blocking functions for distance
	if(watch_sensors) pic_write_state(ECDR_FORWARD, DISTANCE, (uint16_t) distance, 1);
	else pic_write_state(PSNS_FORWARD, DISTANCE, (uint16_t) distance, 1);
}

void CGoodsOut::Reverse(double distance, bool watch_sensors)
{
	DEBUG_METHOD();

	//Set distance to number of counts (each count = 6mm <> divide by 6)
	distance = distance / 6;

	//move forwards - blocking functions for distance
	if(watch_sensors) pic_write_state(ECDR_REVERSE, DISTANCE, (uint16_t) distance, 1);
	else pic_write_state(PSNS_REVERSE, DISTANCE, (uint16_t) distance, 1);
}

void CGoodsOut::TurnLeft90()
{
	DEBUG_METHOD();

	//always 90%
	pic_write_state(COMP_LEFT, NONE, 0, 1);
}

void CGoodsOut::TurnRight90()
{
	DEBUG_METHOD();

	//always 90%
	pic_write_state(COMP_RIGHT, NONE, 0, 1);
}

void CGoodsOut::Stop()
{
	DEBUG_METHOD();

	//Probably redundant
	pic_write_state(STOPPED, NONE, 0, 0);
}

ERoom CGoodsOut::GetCurrentRoomType()
{
	DEBUG_METHOD();

	//just calls the wrapper function!
	return pic_read_roomtype();
}
