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
	CMap(int room_height, int room_width);

	// === Member Variables =========================================================================
private:
	std::vector<std::vector<int>> m_cellMap;
	std::vector<std::vector<ERoom> > m_roomMap;
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

	std::vector<int> m_currentRoom;
	int m_currentVertex;
	EOrientation m_currentOrientation;


	// === Accessor Functions =========================================================================
public:
	std::vector<std::vector<ERoom>>	GetRoomMap() const;
	ERoom GetRoomType(int room_index) const;
	std::vector<std::vector<int>> GetCellMap() const;
	int GetEntranceRoom() const;
	int GetExitRoom() const;
	std::vector<int> GetEntranceCell() const;
	std::vector<int> GetExitCell() const;
	static std::vector<int> GetRoomVertices(ERoom room_type);
	int GetEntranceVertex() const;
	int GetExitVertex() const;

	std::vector<std::vector<int>> GetDistanceMatrix();
	std::vector<std::vector<int>> GetDistanceMatrixCoordinateList();
	//std::vector<int[3]> GetDistanceMatrixArray();

	int GetCurrentVertex() const;
	std::vector<int> GetCurrentRoom() const;

	void SetCurrentRoom(int new_room_index);
	void SetCurrentVertex(int new_vertex_index);



	// === Public Functions =========================================================================

	void UpdateRoomMap();
	void UpdateCellMap();
	void SetCurrentRoomType(ERoom roomType);
	void CalculateBlockRooms(std::vector<int> *pBlockRooms) const;
	std::vector<int> CalculateRoomVertices(int room_index) const;
	std::vector<int> CalculateRoomVertices(int row, int col) const;
	std::vector<double> CalculateVertexCoords(int vertex) const;
	void FollowInstructions(CInstructions &inputInstructions);
	EInstruction FollowInstructionsNotLast(CInstructions &inputInstructions);

	std::vector<std::vector<int>> DistanceMatrix();
	std::vector<std::vector<int>> populateDistanceMatrixFromArray(std::vector<int>exampleArray, int rowCoordinate, int columnCoordinate);

	void WriteCellMap(std::string filepath);


	// === Private Functions ========================================================================
private:
	void CreateRoomMap();
	void ComputeCellMapSize();
	std::vector<int> CalculateRoomVertices(std::vector<int> coord) const;
	std::vector<int> RoomIndextoCoord(int room_index) const;
	
};


#endif /* SRC_CMap_H_ */
