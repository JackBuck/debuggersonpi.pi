/*
 * TopLevel.h
 *
 *  Created on: 23 Feb 2016
 *      Author: Jack Buckingham
 */

#ifndef SRC_TOPLEVEL_H_
#define SRC_TOPLEVEL_H_

#include <vector>

class TopLevel
{
public:
	/* This function will wait for 5 seconds for a button press.
	 * The program will only continue if the button is detected.
	 */
	static void Introduction();

	// Keep introduction! You want to be able to exit if the SPI isn't working!!
	// Only thing is to decide whether to always send the PI to idle


private:
	// This is the idle state on the pi.
	static void IdleState();

	// This function interprets the switches
	static void InterpretSwitches(std::vector<bool> switches, bool askerIsIdleState);

};

#endif /* SRC_TOPLEVEL_H_ */
