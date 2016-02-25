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
int DistanceMatrixTest();
int CGraph_test();
int CGraph_test2();
int CGraph_test3();
int CParseCSV_test();
void CParseCSV_test2();
int CMazeMapper_test();
void CBlockReader_test();
int CBlockReader_test2();
int CBlockReader_test3();
void CBlockReader_test4();
int Challenge1_run_test();
int Challenge2_run_test();
int Challenge3_run_test();
int Challenge4_run_test();

int TestAllFunctions()
{
	DEBUG_METHOD();

	int returnVal = 0;
	// TODO It would be useful to produce output to the console to show which functions 'passed' and which 'failed' so that we can look at their output in the future.
//	returnVal += CMap_test();
//	std::cout << '\n';
//	DistanceMatrixTest();
//	std::cout << '\n';
//	returnVal += CGraph_test();
//	std::cout << '\n';
//	returnVal += CGraph_test2();
//	std::cout << '\n';
//	returnVal += CGraph_test3();
//	std::cout << '\n';
//	returnVal += CParseCSV_test();
//	std::cout << '\n';
//	CParseCSV_test2();
//	std::cout << '\n';
	//CBlockReader_test();                // Will fail without images in the Data/SpotImageExamples folder
	//std::cout << '\n';
	//returnVal += CBlockReader_test2();  // Will fail without images in the Data/SpotImageExamples folder
//	std::cout << '\n';
//	returnVal += CBlockReader_test3();  // Tests ability to use system to take photos (ONLY RUN ON PI)
//	std::cout << '\n';
//	CBlockReader_test4();               // Tests calibration to lighting conditions, and exiftool (ONLY RUN ON PI)
	//std::cout << '\n';
	//returnVal += CMazeMapper_test();
	//std::cout << '\n';
//	returnVal += Challenge1_run_test();
//	std::cout << '\n';
	returnVal += Challenge2_run_test();
	std::cout << '\n';
	returnVal += Challenge3_run_test();
	std::cout << '\n';
	returnVal += Challenge4_run_test();
	std::cout << '\n';



	return returnVal;
}
