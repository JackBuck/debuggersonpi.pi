////////////////////////////////////////////////////////////////////////////////////////////////////
// Sisgnals.cpp
// Created: 15/01/16
// Author: Hannah Howell
//
// This is a place holder for the signal class and has been created so that the functions can be used, 
// the functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.


//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Signals.h"
#include "DebugLog.hpp"


//////////////////////////////////////////////////////////////////////////////////////////
// To signal the start of something.
void CSignals::Start()
{
	DEBUG_METHOD();
}

//////////////////////////////////////////////////////////////////////////////////////////
// To signal the challenge is completed.
void CSignals::Complete()
{
	DEBUG_METHOD();
}

//////////////////////////////////////////////////////////////////////////////////////////
// To signal an error.
void CSignals::Error()
{
	DEBUG_METHOD();
}

//////////////////////////////////////////////////////////////////////////////////////////
// To signal a part of the challenge has been completed. Number 1
void CSignals::Notification1()
{
	DEBUG_METHOD();
}


//////////////////////////////////////////////////////////////////////////////////////////
// To signal a part of the challenge has been completed. Number 2
void CSignals::Notification2()
{
	DEBUG_METHOD();
}


//////////////////////////////////////////////////////////////////////////////////////////
// To signal a part of the challenge has been completed. Number 3
void CSignals::Notification3()
{
	DEBUG_METHOD();
}

// To set the idle state signal
void CSignals::Idle()
{
	// Set green led to flash and blue to off.
}

// To set the challenge state signal
void CSignals::Challenge()
{
	// Set the green led to solid.
	// (Want to be able to use blue led during challenges)
}

void CSignals::Introduction()
{
	// Set green led to flashing and blue to solid
}
