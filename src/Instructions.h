////////////////////////////////////////////////////////////////////////////////////////////////////
// CInstructions.h
// Created: 15/11/15
// Author: Hannah Howell
//

#ifndef SRC_CINSTRUCTIONS_H_
#define SRC_CINSTRUCTIONS_H_

#include <vector>
#include "EnumsHeader.h"

//~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class CInstructions
{
	// === Constructors and Destructors =============================================================
public:
	CInstructions(const std::vector<unsigned int> &labels, const std::vector<unsigned int> &vertexList, const int map_width);
	
	// === Member Variables =========================================================================
private:
	std::vector<EInstruction> m_instructions;
	std::vector<ERoom> m_roomList;
	std::vector<EOrientation> m_orientationBetweenInstructions;


	// === Public Functions =========================================================================
public:
	std::vector<EInstruction>	GetInstructions();

	std::vector<ERoom> GetRoomList();

	std::vector<EOrientation> GetOrientations();

	void TruncateAtRoom(int room_index);

};



#endif SRC_CINSTRUCTIONS_H_

