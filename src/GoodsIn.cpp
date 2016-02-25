////////////////////////////////////////////////////////////////////////////////////////////////////
// GoodsIn.cpp
// Created: 28/01/16
// Author: Hannah Howell
//
// This is a place holder for the GoodsIn class and has been created so that the functions can be used.
// The functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "GoodsIn.h"
#include "DebugLog.hpp"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CGoodsIn::GetJunctionType()
{
	DEBUG_METHOD();
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CGoodsIn::GetRawSensorData()
{
	DEBUG_METHOD();
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CGoodsIn::GetRawCompassData()
{
	DEBUG_METHOD();
}

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This asks the pic whether the button has been pressed since the last request.
 *
 *
 *
 */
bool CGoodsIn::PollButton(vector<bool>& switches)
{
	return false; // TODO: Connect to SPI
}
