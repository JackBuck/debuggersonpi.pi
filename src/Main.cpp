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

void PrintMatrix(std::vector<std::vector<int>> inputMap) {

	for (int i = 0; i < inputMap.size(); i++) {
		for (int j = 0; j < inputMap.size(); j++) {
			std::cout << inputMap[i][j] << " ";
		}
		std::cout << endl;
	}
}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {

	std::ofstream log("DebuggersOnPi.log");
	CRedirecter redirect(log, std::cout);

	int result = TestAllFunctions();
	if (!result)
	// int result = TestAllFunctions();
	//if (!result)
	//{
	//	std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();

	//	Maze.UpdateCellMap();
	//	 
	//	std::vector<std::vector<int>> cellMap = Maze.GetCellMap();
	//}
	//else
	//{
	//	std::cout << "Unable to open file \n";
	//	//return 1;
	//}
	
	std::string hi = "TestData 5x5testmap1.txt";
	std::string filepath = "TestData 5x5testmap1.txt";
	CMap Maze(filepath);


	std::ofstream myfile;
	myfile.open("C:/Users/John/Documents/Programming Stuff/HackSpace/HackspaceProject/TestData/example.txt", std::fstream::out);
	if (myfile.is_open())
	{
		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();

	//std::vector<std::vector<int>> coords = Maze.GetDistanceMatrixCoordinateList();

	//// Printing coordinates list
	//for (int i = 0; i < coords.size(); i++) {
	//	for (int j = 0; j < 3; j++) {
	//		std::cout << coords.at(i).at(j) << " ";
	//	}
	//	std::cout << std::endl;
	}

	//std::cout << "here is the distanceMatrix: \n";

	//// printing distance matrix
	//PrintMatrix(Maze.DistanceMatrix());

	////	std::cin.get();

//	keep_window_open();
	return result;
}
