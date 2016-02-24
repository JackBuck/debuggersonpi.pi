/*
 * TopLevel.cpp
 *
 *  Created on: 23 Feb 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "TopLevel.h"
#include "GoodsIn.h"
#include <vector>
#include <time.h>

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TopLevel::Introduction()
{
	CSignals::Introduction();

	int millisec = 10; // Length of time between polls to the pic, in ms
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = millisec * 1000000L;

	vector<bool> switches;
	for(unsigned int i = 0; i < 5000; ++i)
	{
		if (CGoodsIn::PollButton(switches))
			IdleState();

		nanosleep(&req, (struct timespec *)NULL);
	}
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TopLevel::IdleState()
{
	CSignals::Idle();

	int millisec = 10; // Length of time between polls to the pic, in ms
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = millisec * 1000000L;

	vector<bool> switches;
	while(true)
	{
		if (CGoodsIn::PollButton(switches))
			InterpretSwitches(switches);

		nanosleep(&req, (struct timespec *)NULL);
	}
}

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TopLevel::InterpretSwitches(vector<bool> switches)
{
	// TODO: Include states for 4 challenges, calibration, idle, exit program, shutdown
}
