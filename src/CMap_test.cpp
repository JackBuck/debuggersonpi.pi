#include "CMap.h"
#include<iostream>
#include<fstream>

int main()
{
	std::string filepath = "5x5testmap1.txt";
	CMap Maze(filepath);

	std::ofstream myfile;
	myfile.open("example.txt", std::fstream::out);
	if (myfile.is_open())
	{
		std::vector<std::vector<ERoom>> roomMap = Maze.GetRoomMap();
		for (unsigned int i=0; i<roomMap.size(); i++)
		{
			for (unsigned int j=0; j<roomMap[i].size(); j++)
			{
				std::cout << roomMap[i][j] << "_";
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
