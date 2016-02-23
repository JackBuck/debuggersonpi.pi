#include "CMap.h"
#include<iostream>
#include<fstream>
#include "DebugLog.hpp"


int CMap_test()
{
	DEBUG_METHOD();


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
//
//void PrintMatrix(std::vector<std::vector<int>> inputMap)
//{
//	DEBUG_METHOD();
//
//	for (int i = 0; i < inputMap.size(); i++) {
//		for (int j = 0; j < inputMap.size(); j++) {
//			std::cout << inputMap[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//void CMap_testJohn()
//{
//	DEBUG_METHOD();
//
//
//	std::string filepath = "TestData/5x5testmap1.txt";
//	CMap Maze(filepath);
//
//
//	std::ofstream myfile;
//	myfile.open("TestData/example.txt", std::fstream::out);
//	if (myfile.is_open())
//	{
//		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();
//
//		Maze.UpdateCellMap();
//
//		std::vector<std::vector<int>> cellMap = Maze.GetCellMap();
//	}
//	else
//	{
//		std::cout << "Unable to open file \n";
//		//return 1;
//	}
//
//	myfile.close();
//
//	std::cout << "here is a coordinates list: \n";
//
//	std::vector<std::vector<int>> coords = Maze.GetDistanceMatrixCoordinateList();
//
//	// Printing coordinates list
//	for (int i = 0; i < coords.size(); i++) {
//		for (int j = 0; j < 3; j++) {
//			std::cout << coords.at(i).at(j) << " ";
//		}
//		std::cout << std::endl;
//	}
//
//	std::cout << "here is the distanceMatrix: \n";
//
//	// printing distance matrix
//	PrintMatrix(Maze.DistanceMatrix());
//
//	//	std::cin.get();
//}
