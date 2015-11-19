#include "CMap.h"
#include<iostream>
#include<fstream>

int CMap_test()
{
	std::ofstream myfile;
	myfile.open("example.txt", std::fstream::out);
	if(myfile.is_open())
	{ 
	myfile << "Writing this to a file.\n";
	}
	else 
	{
		std::cout << "Unable to open file \n";
	}

	myfile.close();

	std::string filepath = "5x5testmap1.txt";
	CMap Maze(filepath);

	return 0;
}
