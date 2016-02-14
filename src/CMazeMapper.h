/*
 * CMazeMapper.h
 *
 *  Created on: 7 Feb 2016
 *      Author: Jack Buckingham
 */

#ifndef SRC_CMAZEMAPPER_H_
#define SRC_CMAZEMAPPER_H_

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "EnumsHeader.h"
#include "CMap.h"
#include "CGraph.h"
#include <vector>

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to plan the route when mapping the maze in challenge two.
 */
class CMazeMapper
{
public:
	// === Constructor and Destructors ==============================================================
	CMazeMapper(const CMap*);

	// === Public Functions =========================================================================
	bool ComputeNextVertex(const int& currentVertex, std::vector<int>& outputRoute);
	void Update(const CMap* newMap);

	// === Exceptions ===============================================================================
	struct Exception_NullPointer {};

private:
	// === Member Variables =========================================================================
	std::vector<int> m_vertsToExplore;
	CGraph m_currentGraph;
	const CMap* m_pCurrentMap;

	// === Private Functions ========================================================================
	void FindVertsToExplore();
	double VertexScore(int vertex);
};

#endif /* SRC_CMAZEMAPPER_H_ */
