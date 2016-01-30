////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.h
// Created: 15/11/15
// Author: Hannah Howell
//

#ifndef SRC_CMAP_H_
#define SRC_CMAP_H_



//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "EnumsHeader.h"
#include<vector>
#include<string>

//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CMap
{
	// === Constructors and Destructors =============================================================
public:
	CMap(std::string filepath);
	CMap(std::vector<std::vector<int>> inputMap, int start, int finish);
	CMap(int room_height, int room_width);

	// === Member Variables =========================================================================
private:
	std::vector<std::vector<int>> m_cellMap;
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

	std::vector<std::vector<int>> GetCellMap();

	void UpdateRoomMap();

	void UpdateCellMap();

	static std::vector<int> GetRoomVertices(ERoom room_type);

	// === Private Functions ========================================================================
private:
	void CreateRoomMap();
	void ComputeCellMapSize();
};



#endif SRC_CMap_H_
