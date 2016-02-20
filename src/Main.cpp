/*
 * Main.cpp
 *
 *  Created on: 19 Nov 2015
 *      Author: Jack Buckingham
 *
 *
 * A file to contain the main() function.
 * This function will be edited according to what we want to do.
 * E.g. - Calling functions from TestFunctions.cpp to test functionality of our code;
 *      - Calling the functions for the 4 challenges posed to the robot
 *      - When we get there, calling the top level of the robot, which will call the 4 challenge functions on the day.
 *
 * Note, this is really to help us while we are developing the robot.
 * The final version of the software (or in fact any version which we compile for the pi) needn't use this file.
 *
 */


// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include<iostream>
#include<fstream>
#include "DebugLog.hpp"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// Declare TestallFunctions
int TestAllFunctions();

// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Keep the window open on windows systems without restricting the program to windows systems
inline void keep_window_open()
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{

#ifdef DEBUG_LOG_ENABLE
	ofstream log("DebuggersOnPi.log");
	CRedirecter redirect(log, cout);
#endif

	int result = TestAllFunctions();
	if (!result)
	{
		cout << "All tests completed successfully!\n";
	}
	else
	{
		cout << "Error! One or more tests failed!\n";
	}



//	keep_window_open(); // Commented since logger redirects output to file, so you don't see the enter character message!!
	return result;
}
