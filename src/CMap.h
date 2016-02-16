////////////////////////////////////////////////////////////////////////////////////////////////////
// CMap.h
// Created: 15/11/15
// Author: Hannah Howell
//

#ifndef SRC_CMAP_H_
#define SRC_CMAP_H_



//~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "EnumsHeader.h"
#include "Instructions.h"
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
	std::vector<std::vector<ERoom>> m_roomMap;
	int m_cellheight;
	int m_cellwidth;
	int m_firstRoom;
	int m_exitRoom;
	std::vector<int> m_entranceCell;
	std::vector<int> m_exitCell;
	std::vector<int[3]> m_distanceMatrixArray;
	std::vector<std::vector<int>> m_distanceMatrixCoordinateList;
	std::vector<std::vector<int>> m_distanceMatrix;

	// === Location Tracking ==========================================================================

	int m_currentRoom;
	int m_currentVertex;


	// === Accessor Functions =========================================================================
public:
	std::vector<std::vector<ERoom>>	GetRoomMap();
	ERoom GetRoomType(int room_index);
	std::vector<std::vector<int>> GetCellMap();
	int GetEntranceRoom();
	int GetExitRoom();
	std::vector<int> GetEntranceCell();
	std::vector<int> GetExitCell();
	static std::vector<int> GetRoomVertices(ERoom room_type);
	int GetEntranceVertex();
	int GetExitVertex();
	std::vector<std::vector<int>> GetDistanceMatrix();
	std::vector<std::vector<int>> GetDistanceMatrixCoordinateList();
	//std::vector<int[3]> GetDistanceMatrixArray();

	int GetCurrentVertex();
	int GetCurrentRoom();

	void SetCurrentRoom(int new_room);
	void SetCurrentVertex(int new_vertex);



	// === Public Functions =========================================================================

	void UpdateRoomMap();
	void UpdateCellMap();
	void CalculateBlockRooms(std::vector<int> *pBlockRooms);
	std::vector<int> CalculateRoomVertices(int room_index);
	void FollowInstructions(CInstructions &inputInstructions);
	std::vector<std::vector<int>> DistanceMatrix();
	std::vector<std::vector<int>> CMap::populateDistanceMatrixFromArray(std::vector<int>exampleArray, int rowCoordinate, int columnCoordinate);



	// === Private Functions ========================================================================
private:
	void CreateRoomMap();
	void ComputeCellMapSize();
	std::vector<int> RoomIndextoCoord(int room_index);
	
};


#endif /* SRC_CMap_H_ */
