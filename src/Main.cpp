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
#include "CMap.h"
#include<fstream>

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

std::vector<std::vector<int>> populateDistanceMatrixFromArray(int exampleArray[4], int rowCoordinate, int columnCoordinate, int matrixSize) {
	
	int n = matrixSize;
	int distanceMatrixSize = (n - 1)*(2 * (n + 1) + 1) + (5 * n) - 2;

	// TODO:
	// testing stage complete.
	// Implement into the rest of the function so it can be used normally as a method
	// ENSURE THAT i & j > n !!!
	// if so, throw exception "n must be > than row & column coordinates"

	// x = i(2n + 1) + 2j
	// y = x + 2n + 2

	int i_coordinate = rowCoordinate;
	int j_coordinate = columnCoordinate;

	int vertexA_Coordinate = 0, vertexB_Coordinate = 0;
	int edge_Magnitude;

	int firstVertexOfRoom = i_coordinate * ((2 * n) + 1) + 2*j_coordinate;

	int NorthVertexCoordinate = firstVertexOfRoom + 1;
	int EastVertexCoordinate = firstVertexOfRoom + 2;

	// by default, the southvertex number is the following. However, if the room is on the last row, the equation changes slightly
	int SouthVertexCoordinate = firstVertexOfRoom + (2 * n) + 2;
	if (i_coordinate == n - 1) {
		SouthVertexCoordinate = firstVertexOfRoom + (2 * n) + 1;
	}

	int WestVertexCoordinate = firstVertexOfRoom;

	int convertedVertexArray[4] = { NorthVertexCoordinate, EastVertexCoordinate, SouthVertexCoordinate, WestVertexCoordinate };

	// Creating a distanceMatrix of zeros
	std::vector<std::vector<int>> distanceMatrix(distanceMatrixSize);
	for (int i = 0; i < distanceMatrixSize; i++) {
		distanceMatrix[i].resize(distanceMatrixSize);
	}

	// Main body of function:

	for (int i = 0; i < 4; i++)
	{		
		if (exampleArray[i] != 0)
		{
			// if != 0, the a coordinate is convertedVertexArray[i]
			
			vertexA_Coordinate = convertedVertexArray[i];


			// loop through the rest of the integers in the array to see if any of them are non-zero
			for (int j = i + 1; j < 4; j++) {

				// if there is another non-zero value, the b coordinate is convertedVertexArray[j]
				if (exampleArray[j] != 0) {
					vertexB_Coordinate = convertedVertexArray[j];

					// coordinates are only added if both vertices are non-zero
					if (j == i + 1 || j == i + 3) {
						edge_Magnitude = 2;
					}
					else if (j == i + 2) {
						edge_Magnitude = 1;
					}
					else { edge_Magnitude = 0; }


					if (vertexA_Coordinate < vertexB_Coordinate) {

						// Logic needs to be added to discern whether the room is a corner or a straight line
						distanceMatrix.at(vertexB_Coordinate).at(vertexA_Coordinate) = edge_Magnitude;
					}

					// Added in case vertexA_Coordinate == vertexB_Coordinate (which should never happen)
					else if (vertexA_Coordinate > vertexB_Coordinate) {

						// Logic needs to be added to discern whether the room is a corner or a straight line
						distanceMatrix.at(vertexA_Coordinate).at(vertexB_Coordinate) = edge_Magnitude;
					}
				}


				// check which is greater than the other.
				// (a,b) a should be greater than b in all cases
				// give the room a magnitude
				// Then populate the distanceMatrix with the magnitude at (a,b)
				// Then add to the distanceMatrixCoordinateArray the same.
			}
		}
	}


	return distanceMatrix;
}



//std::vector<std::vector<int>> populateDistanceMatrixFromArray(int exampleArray[4], int rowCoordinate, int columnCoordinate, int matrixSize) {
//
//	int n = matrixSize;
//	int distanceMatrixSize = (n - 1)*(2 * (n + 1) + 1) + (5 * n) - 2;
//
//	// TODO:
//	// testing stage complete.
//	// Implement into the rest of the function so it can be used normally as a method
//	// ENSURE THAT i & j > n !!!
//	// if so, throw exception "n must be > than row & column coordinates"
//
//	// x = i(2n + 1) + 2j
//	// y = x + 2n + 2
//
//	int i_coordinate = rowCoordinate;
//	int j_coordinate = columnCoordinate;
//
//	int vertexA_Coordinate = 0, vertexB_Coordinate = 0;
//	int edge_Magnitude;
//
//	int firstVertexOfRoom = i_coordinate * ((2 * n) + 1) + 2 * j_coordinate;
//
//	int NorthVertexCoordinate = firstVertexOfRoom + 1;
//	int EastVertexCoordinate = firstVertexOfRoom + 2;
//
//	// by default, the southvertex number is the following. However, if the room is on the last row, the equation changes slightly
//	int SouthVertexCoordinate = firstVertexOfRoom + (2 * n) + 2;
//	if (i_coordinate == n - 1) {
//		SouthVertexCoordinate = firstVertexOfRoom + (2 * n) + 1;
//	}
//
//	int WestVertexCoordinate = firstVertexOfRoom;
//
//	int convertedVertexArray[4] = { NorthVertexCoordinate, EastVertexCoordinate, SouthVertexCoordinate, WestVertexCoordinate };
//
//	// Creating a distanceMatrix of zeros
//	std::vector<std::vector<int>> distanceMatrix(distanceMatrixSize);
//	for (int i = 0; i < distanceMatrixSize; i++) {
//		distanceMatrix[i].resize(distanceMatrixSize);
//	}
//
//	//std::vector<int[3]> distanceMatrixCoordinateList;
//
//	// Main body of function:
//	for (int i = 0; i < 4; i++)
//	{
//		if (exampleArray[i] != 0)
//		{
//			// if != 0, the a coordinate is convertedVertexArray[i]
//
//			vertexA_Coordinate = convertedVertexArray[i];
//
//
//			// loop through the rest of the integers in the array to see if any of them are non-zero
//			for (int j = i + 1; j < 4; j++) {
//
//				// if there is another non-zero value, the b coordinate is convertedVertexArray[j]
//				if (exampleArray[j] != 0) {
//					vertexB_Coordinate = convertedVertexArray[j];
//
//					// coordinates are only added if both vertices are non-zero
//					if (j == i + 1 || j == i + 3) {
//						edge_Magnitude = 2;
//					}
//					else if (j == i + 2) {
//						edge_Magnitude = 1;
//					}
//					else { edge_Magnitude = 0; }
//
//
//					if (vertexA_Coordinate < vertexB_Coordinate) {
//
//						distanceMatrix.at(vertexB_Coordinate).at(vertexA_Coordinate) = edge_Magnitude;
//						// distanceMatrixCoordinateList.push_back({ vertexB_Coordinate, vertexA_Coordinate, edge_Magnitude });
//					}
//
//					else if (vertexA_Coordinate > vertexB_Coordinate) {
//
//						distanceMatrix.at(vertexA_Coordinate).at(vertexB_Coordinate) = edge_Magnitude;
//						// distanceMatrixCoordinateList.push_back({ vertexA_Coordinate, vertexB_Coordinate, edge_Magnitude });
//					}
//				}
//
//
//				// check which is greater than the other.
//				// (a,b) a should be greater than b in all cases
//				// give the room a magnitude
//				// Then populate the distanceMatrix with the magnitude at (a,b)
//				// Then add to the distanceMatrixCoordinateArray the same.
//			}
//		}
//	}
//
//	//std::cout << "distance matrix coordinate list: \n";
//	//for (int i = 0; i < distanceMatrixCoordinateList.size(); i++) {
//	//	for (int j = 0; j < 3; j++) {
//	//		std::cout << distanceMatrixCoordinateList[j] << " ";
//	//	}
//	//	std::cout << std::endl;
//	//}
//
//	return distanceMatrix;
//}


// ~~~ FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
	// int result = TestAllFunctions();
	//if (!result)
	//{
	//	cout << "All tests completed successfully!\n";
	//}
	//else
	//{
	//	cout << "Error! One or more tests failed!\n";
	//}
	
	std::string filepath = "C:/Users/John/Documents/Programming Stuff/HackSpace/HackspaceProject/TestData/5x5testmap1.txt";
	CMap Maze(filepath);

	std::ofstream myfile;
	myfile.open("C:/Users/John/Documents/Programming Stuff/HackSpace/HackspaceProject/TestData/example.txt", std::fstream::out);
	if (myfile.is_open())
	{
		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();

		Maze.UpdateCellMap();
		 
		std::vector<std::vector<int>> cellMap = Maze.GetCellMap();

		//for (unsigned int i = 0; i<cellMap.size(); i++)
		//{
		//	for (unsigned int j = 0; j<cellMap[i].size(); j++)
		//	{
		//		std::cout << cellMap[i][j];
		//	}
		//	std::cout << std::endl;
		//}


	}
	else
	{
		std::cout << "Unable to open file \n";
		//return 1;
	}

	myfile.close();


	std::cout << "Here is the distanceMatrix: \n "<< std::endl;
	
	PrintMatrix(Maze.DistanceMatrix());

	std::cout << "here is the distanceMatrix after inputting an exampleArray: \n";

	std::vector<int> exampleArray = { 1,1,1,1 };

	Maze.GetRoomMap();

	PrintMatrix(Maze.populateDistanceMatrixFromArray(exampleArray, 1,1));

	//	std::cin.get();

	keep_window_open();
	//return result;
}
