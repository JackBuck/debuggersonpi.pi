#include "CMap.h"
#include<iostream>
#include<fstream>

int CMap_test()
{
	std::string filepath = "5x5testmap1.txt";
	CMap Maze(filepath);

	std::ofstream myfile;
	myfile.open("example.txt", std::fstream::out);
	if (myfile.is_open())
	{
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
		return 0;
	}

	myfile.close();
	
	std::cin.get();
	return 0;
}
