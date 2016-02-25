/*
 * TopLevel.cpp
 *
 *  Created on: 23 Feb 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "TopLevel.h"
#include "GoodsIn.h"
#include "Signals.h"
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

/* ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function interprets the switches
 */
void TopLevel::InterpretSwitches(vector<bool> switches)
{
	// TODO: Include states for 4 challenges, calibration, idle, exit program, shutdown, test switch directions

	if (switches == vector<bool> {0,0,0,0}) // Test the direction of the switches (TODO: Change this to test left and right as well -- eg green flash for 1010 and blue for 0101?)
	{
		CSignals::BothLeds(2000);
	}

	else if (switches == vector<bool> {true, true, true, true})    // 1111 -- Idle
		IdleState(); // TODO: Get rid of Introduction asap so that this can just return us to the idle state (don't want an inception situation!)

	else if (switches == vector<bool> {true, false, false, false}) // 1000 -- Challenge one
		CChallenges::ChallengeOne();

	else if (switches == vector<bool> {false, true, false, false}) // 0100 -- Challenge two
			CChallenges::ChallengeOne();

	else if (switches == vector<bool> {false, false, true, false}) // 0010 -- Challenge three
			CChallenges::ChallengeOne();

	else if (switches == vector<bool> {false, false, false, true}) // 0001 -- Challenge four
			CChallenges::ChallengeOne();

	else if (switches == vector<bool> {true, true, false, false})   // 1100 -- Shut down
	{
		// TODO: Shutdown
	}

	else if (switches == vector<bool> {true, false, true, false})    // 1110 -- Exit to commandline // TODO: Change this since
	{
		// TODO: Exit to commandline
	}

	else if (switches == vector<bool> {})
	{

	}

	else
	{
		//TODO: flash both LEDS to signal erroneous input
		IdleState(); //
	}
}
