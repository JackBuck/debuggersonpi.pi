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
 *
 * Public Constructors:
 *    - CMazeMapper(const CMap*) - Initialises the CMazeMapper with a CMap pointer.
 *
 * Public Methods:
 *    - ComputeNextVertex(...) - A method to find the route to the next vertex to explore. Returns
 *    	false if no more vertices need exploring.
 *
 *    - Update(const CMap*) - Updates the CMazeMapper with a new CMap pointer and recomputes the
 *    	vertices to explore.
 *
 * Exceptions:
 * 	- Exception_NullPointer - Thrown when a null pointer is passed either to the constructor or to
 * 		the Update method.
 *
 */
class CMazeMapper
{
public:
	// === Constructor and Destructors ==============================================================
	CMazeMapper(CMap*);

	// === Public Functions =========================================================================
	bool ComputeNextVertex(const int& currentVertex, std::vector<int>& outputRoute);
	void Update(CMap* newMap);

	// === Exceptions ===============================================================================
	struct Exception_NullPointer {};

private:
	// === Member Variables =========================================================================
	std::vector<int> m_vertsToExplore;
	CMap* m_pCurrentMap;

	// === Private Functions ========================================================================
	void FindVertsToExplore();
	double VertexScore(int vertex);
};

#endif /* SRC_CMAZEMAPPER_H_ */
