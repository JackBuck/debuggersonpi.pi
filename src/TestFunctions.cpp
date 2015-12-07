/*
 * TestFunctions.cpp
 *
 *  Created on: 19 Nov 2015
 *      Author: Jack Buckingham
 *
 * A file containing functions where we can call various sets of test functions written for parts of our program.
 * When a test is written, it should be called in the relevant functions in this file.
 * The functions in this file will then be called from the main function, found in Main.cpp, when we wish to debug.
 */

#include<iostream>

int CMap_test();
int CGraph_test();

int TestAllFunctions()
{
	int returnVal = 0;
	// TODO It would be useful to produce output to the console to show which functions 'passed' and which 'failed' so that we can look at their output in the future.
	returnVal += CMap_test();
	std::cout << '\n';
	returnVal += CGraph_test();
	std::cout << '\n';

	return returnVal;
}
