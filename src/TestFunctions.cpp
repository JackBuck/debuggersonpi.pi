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
#include "DebugLog.hpp"

int CMap_test();
void CMap_testJohn();
int CGraph_test();
int CGraph_test2();
int CGraph_test3();
int CParseCSV_test();
void CParseCSV_test2();
int CMazeMapper_test();
void CBlockReader_test();
int CBlockReader_test2();


int TestAllFunctions()
{
	DEBUG_METHOD();

	int returnVal = 0;
	// TODO It would be useful to produce output to the console to show which functions 'passed' and which 'failed' so that we can look at their output in the future.
	returnVal += CMap_test();
	//std::cout << '\n';
	//CMap_testJohn();
	//std::cout << '\n';
	//returnVal += CGraph_test();
	//std::cout << '\n';
	//returnVal += CGraph_test2();
	//std::cout << '\n';
	//returnVal += CGraph_test3();
	//std::cout << '\n';
	//returnVal += CParseCSV_test();
	//std::cout << '\n';
	//CParseCSV_test2();
	//std::cout << '\n';
	//CBlockReader_test();                // Will fail without images in the Data/SpotImageExamples folder
	//std::cout << '\n';
	//returnVal += CBlockReader_test2();  // Will fail without images in the Data/SpotImageExamples folder
	//std::cout << '\n';
	//returnVal += CMazeMapper_test();
	//std::cout << '\n';



	return returnVal;
}
