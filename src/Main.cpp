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
#include "CMap.h"
#include<fstream>
#include<fstream>
#include "DebugLog.hpp"

#include "CMap.h"

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

int DistanceMatrixTest()
{
	/////////////////////////////////////////////////////////////
	// Create instance of CMap 
	std::string fileInputpath = "TestData/PracticeMap.csv";
	CMap Maze(fileInputpath);

	/////////////////////////////////////////////////////////////
	//
	std::ofstream myfile;
	myfile.open("TestData/example.txt", std::fstream::out);
	if (myfile.is_open())
	{
		std::cout << "--CMap_test--\n\n";

		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();

		Maze.UpdateCellMap();

		std::vector<std::vector<int>> cellMap = Maze.GetCellMap();

		for (unsigned int i = 0; i<cellMap.size(); i++)
		{
			for (unsigned int j = 0; j<cellMap[i].size(); j++)
			{
				std::cout << cellMap[i][j];
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "Unable to open file \n";
		return 1;
	}

	myfile.close();
	
	std::string fileOutputPath = "TestData/5x5testmap1Output.txt";
	Maze.WriteCellMap(fileOutputPath);
	return 0;
}

void PrintMatrix(std::vector<std::vector<int>> inputMap)
{

	for (int i = 0; i < inputMap.size(); i++) {
		for (int j = 0; j < inputMap.size(); j++) {
			std::cout << inputMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void CMap_testJohn()
{
	std::string filepath = "TestData/5x5testmap1.txt";
	CMap Maze(filepath);

	std::ofstream myfile;
	myfile.open("TestData/example.txt", std::fstream::out);
	if (myfile.is_open())
	{
		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();

		Maze.UpdateCellMap();

		std::vector<std::vector<int>> cellMap = Maze.GetCellMap();
	}
	else
	{
		std::cout << "Unable to open file \n";
		//return 1;
	}

	myfile.close();

	std::cout << "here is a coordinates list: \n";

	std::vector<std::vector<int>> coords = Maze.GetDistanceMatrixCoordinateList();

	// Printing coordinates list
	for (int i = 0; i < coords.size(); i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << coords.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "here is the distanceMatrix: \n";

	// printing distance matrix
	PrintMatrix(Maze.DistanceMatrix());

	//	std::cin.get();
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

	



	//ep_window_open(); // Commented since logger redirects output to file, so you don't see the enter character message!!
	//return result;
	

	//DistanceMatrixTest();
	// CMap_testJohn();


	//std::vector<std::vector<ERoom>> testMap = { {ERoom_EastSouthWest, ERoom_EastSouth},
	//										{ERoom_NorthSouth, ERoom_NorthEastSouth} };

	std::string filepath = "C:/Users/John/Documents/Programming Stuff/HackSpace/HackspaceProject/TestData/PracticeMap.csv";
	CMap Maze(filepath);


	PrintMatrix(Maze.DistanceMatrix());
	keep_window_open();

}


