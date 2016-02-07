/*
 * CMazeMapper.h
 *
 *  Created on: 7 Feb 2016
 *      Author: Jack Buckingham
 */

#ifndef SRC_CMAZEMAPPER_H_
#define SRC_CMAZEMAPPER_H_

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to plan the route when mapping the maze in challenge two.
 */
class CMazeMapper
{
public:
	CMazeMapper();

	void ComputeNextVertex(const CMap& currentMap, const int& currentVertex, std::vector<int>& outputRoute);
	void AnalyseMap(const CMap& newMap);

private:
	std::vector<int> m_vertsToExplore;
};

#endif /* SRC_CMAZEMAPPER_H_ */
