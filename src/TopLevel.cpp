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

#include <cstdlib>  // For system() and exit()

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
 * This function interprets the switches.
 *
 * INPUTS:
 * switches - This is a 4-element vector containing the state of the switches to be evaluated.
 *
 * askerIsIdleState - This is a bool to determine whether the calling function is the idle state.
 * 	If this is true then the function will simply return. If it is false then it will explicitly call the idle state.
 *
 * 	!!WARNING!! -- To avoid an inception style sequence of events, only pass this as false if coming from the Introduction state.
 * 	               Needless to say, only pass it as true if coming from idle.
 * 	               If you want to read the switches in a different function you will need to do something more complicated!
 *
 */
void TopLevel::InterpretSwitches(vector<bool> switches, bool askerIsIdleState)
{

	if (switches == vector<bool> { 0, 0, 0, 0 })      // 0000 -- Idle
	{
		if (!askerIsIdleState)
			IdleState(); // Should only be called from Introduction
		else
			return; // Return control to the idle state
	}

	else if (switches == vector<bool> { 1, 0, 0, 0 }) // 1000 -- Challenge one
		CChallenges::ChallengeOne();

	else if (switches == vector<bool> { 0, 1, 0, 0 }) // 0100 -- Challenge two
		CChallenges::ChallengeOne();

	else if (switches == vector<bool> { 0, 0, 1, 0 }) // 0010 -- Challenge three
		CChallenges::ChallengeOne();

	else if (switches == vector<bool> { 0, 0, 0, 1 }) // 0001 -- Challenge four
		CChallenges::ChallengeOne();

	else if (switches == vector<bool> { 1, 1, 1, 1 }) // 1111 -- Shut down
	{
		// Check we can use system()
		if (!system(NULL))
		{
			cout << "Unable to use system() to call other processes.\n";
			exit(1);
		}

		system("sudo shutdown -h now");

	}

	else if (switches == vector<bool> { 1, 0, 1, 0 }) // 1010 -- Exit to commandline
	{
		exit(0);
	}

	else if (switches == vector<bool> { 1, 1, 0, 0 }) // 1100 -- Calibration (Take photo to get lighting conditions)
	{
		CBlockReader aBlockReader;
		aBlockReader.CalibrateFromPhoto();
	}

	else
	{
		//TODO: flash both LEDS to signal erroneous input for 2 seconds

		if (!askerIsIdleState)
			IdleState();
		else
			return;
	}
}
