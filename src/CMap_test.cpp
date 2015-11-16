


#include "CMap.h"
#include<iostream>
#include<fstream>


inline int CMap_test()
{
	std::ofstream myfile;
	myfile.open("example.txt");
	if(myfile.is_open())
	{ 
	myfile << "Writing this to a file.\n";
	}
	else 
	{
		std::cout << "Unable to open files \n";
	}

	myfile.close();

	std::string filepath = "5x5testmap1.txt";
	CMap aMap {filepath};
//	CMap::CMap(filepath);

	return 0;

}
