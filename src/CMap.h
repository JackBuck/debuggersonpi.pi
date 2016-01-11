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

enum ERoom
{
	ERoom_Empty,
	ERoom_Cross,
	ERoom_NorthSouth,
	ERoom_EastWest,
	ERoom_EastSouthWest,
	ERoom_NorthSouthWest,
	ERoom_NorthEastWest,
	ERoom_NorthEastSouth,
	ERoom_NorthWest,
	ERoom_NorthEast,
	ERoom_EastSouth,
	ERoom_SouthWest,
	ERoom_North,
	ERoom_East,
	ERoom_South,
	ERoom_West
};

enum EInstruction
{
	EInstruction_Stop,
	EInstruction_Start,
	EInstruction_Straight,
	EInstruction_TurnLeft,
	EInstruction_TurnRight,
	EInstruction_LAST
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
	std::vector<std::vector<ERoom>> m_roomMap;
	std::vector<int[2]> m_currentPath;
	int m_pathLocation;


	// === Public Functions =========================================================================
public:
	std::vector<std::vector<ERoom>>	GetRoomMap();

	// === Private Functions ========================================================================
private:
	void CreateRoomMap();
	void ComputeMapSize();

};



#endif // SRC_CMap_H_
