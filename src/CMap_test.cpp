#include "CMap.h"
#include<iostream>
#include<fstream>
#include "DebugLog.hpp"


int CMap_test()
{
	DEBUG_METHOD();


	/////////////////////////////////////////////////////////////
	// Create instance of CMap 
	std::string fileInputpath = "5x5testmap1.txt";
	CMap Maze(fileInputpath);

	/////////////////////////////////////////////////////////////
	//
	std::ofstream myfile;
	myfile.open("example.txt", std::fstream::out);
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

	std::string fileOutputPath = "5x5testmap1Output.txt";
	Maze.WriteCellMap(fileOutputPath);
	return 0;
}
