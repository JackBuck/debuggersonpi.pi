////////////////////////////////////////////////////////////////////////////////////////////////////
// Signals.h
// Created: 15/01/16
// Author: Hannah Howell
//

// This is a place holder for the signal class and has been created so that the functions can be used 
// the functions are currently empty and do nothing. Any functions that use these place holders will 
// need to be checked when the class is completed.


#ifndef SRC_CSignals_H_
#define SRC_CSignals_H_

//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CSignals
{

	// === Public Functions =========================================================================
public:
	static void Start();
	static void Complete();
	static void Error();
	static void Notification1();
	static void Notification2();
	static void Notification3();

	static void Introduction();
	static void Idle();
	static void Challenge();
	static void BothLeds(int milliseconds);

};


#endif /* SRC_CChallenges_H_ */
