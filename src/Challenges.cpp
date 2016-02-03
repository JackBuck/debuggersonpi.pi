////////////////////////////////////////////////////////////////////////////////////////////////////
// Challenges.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

#include "Challenges.h"
#include "CMap.h"
#include "CGraph.h"
#include "Instructions.h"
#include "Signals.h"
#include "GoodsIn.h"
#include "GoodsOut.h"
#include "Manouvre.h"
#include <climits>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Basic outline of challenge 1 I am not sure how the interupts will work exactly.
void CChallenges::ChallengeOne()
{
	CSignals::Start();

	bool interrupt = false;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Tell pic to follow line forever (or near enough) unless interrupted.

	CGoodsOut::Forward(INT_MIN, true);

	int count = 0;

	while(!interrupt)
	{
		count++;

		if(count == 10000)
		{
			CSignals::Notification1();
			count = 0;
		}

	}

	CGoodsOut::Stop();

	CSignals::Complete();
}

void CChallenges::ChallengeTwo()
{
	std::string filepath;
	CMap aMap = CMap(filepath);
	int entrance_vertex = aMap.GetEntranceVertex();
	int exit_vertex = aMap.GetExitVertex();
	
	std::vector<std::vector<double>> distanceMatrix;
	std::vector<unsigned int> labels;
	///////////////////////////// Call Johns Function to populate these


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Generate graph of map.

	CGraph aGraph = CGraph(distanceMatrix, labels);


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Calculate shortest route from start to finish.

	double shortest_distance;
	std::vector<unsigned int> outputRoute;
	aGraph.ShortestDistance(entrance_vertex, exit_vertex, shortest_distance, outputRoute);


	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute macro instructions.

	CInstructions aInstructions = CInstructions(labels, outputRoute, 10);

	std::vector<EInstruction> macroInstructions = aInstructions.GetInstructions();


	//////////////////////////////////////////////////////////////////////////////////////////////
	// Now we know our route, execute it!



}

void CChallenges::ChallengeThree()
{

}

void CChallenges::ChallengeFour()
{

}
