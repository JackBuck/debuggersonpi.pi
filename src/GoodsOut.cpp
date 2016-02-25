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

void CGoodsOut::ForwardDistance(double distance, bool PSControlTheory)
{
	DEBUG_METHOD();

	uint16_t tempcounts = (uint16_t) distance / 6;
	if(PSControlTheory) pic_write_state(PSNS_FORWARD,COUNTS,(uint16_t) tempcounts, 1);
	else 					  pic_write_state(OL_FORWARD, COUNTS, (uint16_t) tempcounts, 1);
}

ERoom CGoodsOut::ForwardDetectJunction()
{

	DEBUG_METHOD();

	pic_write_state(PSNS_FORWARD_JUNCTION_DETECT, JUNCTION, 0, 1);

	ERoom Result;
	pic_read_roomtype(&Result);
	return Result;
}


void CGoodsOut::Reverse(double distance, bool PSControlTheory)
{
	DEBUG_METHOD();

	uint16_t tempcounts = (uint16_t) distance / 6;
	if(PSControlTheory) pic_write_state(PSNS_REVERSE,COUNTS,(uint16_t) tempcounts, 1);
	else 					  pic_write_state(OL_REVERSE, COUNTS, (uint16_t) tempcounts, 1);

}

void CGoodsOut::TurnLeft90()
{
	DEBUG_METHOD();

	pic_write_state(COMP_LEFT, NONE_CONDITION_T, 0, 1);
}

void CGoodsOut::TurnRight90()
{
	DEBUG_METHOD();

	pic_write_state(COMP_RIGHT, NONE_CONDITION_T, 0, 1);
}

void CGoodsOut::Stop()
{
	DEBUG_METHOD();

	pic_write_state(STOPPED, NONE_CONDITION_T, 0, 0);
}

ERoom CGoodsOut::GetCurrentRoomType()
{
	DEBUG_METHOD();

	ERoom Result;
	pic_read_roomtype(&Result);
	return Result;
}
