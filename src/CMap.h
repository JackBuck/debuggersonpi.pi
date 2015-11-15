////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.h
// Created: 15/11/15
// Author: Hannah Howell
//

#ifndef SRC_CMAP_H_
#define SRC_CMAP_H_




//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include<vector>
#include<string>


// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

enum room_type
{
	Blank,
	Cross,
	NorthSouth,
	EastWest,
	EastSouthWest,
	NorthSouthWest,
	NorthEastWest,
	NorthEastSouth,
	NorthWest,
	NorthEast,
	EastSouth,
	SouthWest,
	North,
	East,
	South,
	West
};

enum instruction
{
	Stop, 
	Start,
	Straight,
	TurnLeft,
	TurnRight,
	LAST
};

//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CMap
{
	// === Constructors and Destructors =============================================================
public:
	CMap(std::string filepath);
	CMap(std::vector<std::vector<int>> inputMap, int start, int finish);
	// === Member Variables =========================================================================
private:
	std::vector<std::vector<int>> m_map;
	int m_start;
	int m_finish;
	int m_height;
	int m_width;
	std::vector<std::vector<int>> m_roomMap;
	std::vector<int[2]> m_currentPath;
	int m_pathLocation;


	// === Public Functions =========================================================================
public:


	// === Private Functions ========================================================================
private:
	void CreateRoomMap();
	void ComputeMapSize();

};



#endif  SRC_CGRAPH_H_ 