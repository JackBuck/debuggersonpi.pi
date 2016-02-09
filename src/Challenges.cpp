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
	



}

void CChallenges::ChallengeThree()
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


	std::vector<unsigned int> outputRoute;
	aGraph.ShortestDistance(entrance_vertex, exit_vertex, outputRoute);


	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute macro instructions.

	CInstructions aInstructions = CInstructions(labels, outputRoute, 10);

	std::vector<EInstruction> macroInstructions = aInstructions.GetInstructions();


	//////////////////////////////////////////////////////////////////////////////////////////////
	// Now we know our route, execute it

	CManouvre::MoveToStartVertex();

	for(unsigned int i=0; i<macroInstructions.size(); i++)
	{
		CManouvre::InstructionToManouvre(macroInstructions[i]);
	}

	CManouvre::ExitMap();

	CGoodsOut::Stop();

	CSignals::Complete();
}



void CChallenges::ChallengeFour()
{
	///////////////////////////////////////////////////////////////////////
	// Import map
	std::string filepath;
	CMap aMap = CMap(filepath);


	////////////////////////////////////////////////////////////////////////
	// Set the current room as the starting room of the map.
	int current_room = aMap.GetEntranceRoom();

	///////////////////////////////////////////////////////////////////////
	// Set start_vertex as entrance vertex.
	int start_vertex = aMap.GetEntranceVertex;

	///////////////////////////////////////////////////////////////////////
	// The value on the current block of interest.
	int next_value = 1;

	///////////////////////////////////////////////////////////////////////
	// Locations of blocks if unknown -1
	
	int LOCATION_UNKNOWN = -1;
	std::vector<int> block_location;
	block_location = {LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN};


	//////////////////////////////////////////////////////////////////////
	// Rooms containing blocks whose value is unknown.

	std::vector<int> unknown_block_rooms;
	aMap.CalculateBlockRooms(&unknown_block_rooms);

	
	while(next_value <=5)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////
		// Create variable to hold next path.

		std::vector<int> planned_path;

		//////////////////////////////////////////////////////////////////////
		// Check if location of next block is known.

		if(block_location[next_value] == LOCATION_UNKNOWN)
		{
			std::vector<std::vector<double>> distanceMatrix;
			std::vector<unsigned int> labels;

			
			// Calculated by Johns function.

			CGraph aGraph = CGraph::CGraph(distanceMatrix, labels);

			///////////////////////////////////////////////////////////////////////////////////
			// TODO this could be moved onto the CGraph class.

			//////////////////////////////////////////////////////////////////////////////////
			// Keep track of shortest distance and path and start vertex

			int start_vertex;
			double shortest_distance = LONG_MAX;
			std::vector<int> shortest_path;


			//////////////////////////////////////////////////////////////////////
			// Get current room type and the vertex labels of adjacent vertices.

			ERoom start_room_type = aMap.GetRoomType(current_room);
			std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(current_room);


			/////////////////////////////////////////////////////////////////////////////
			// Check which of these vertices exist.

			std::vector<int> existingVerticesOfStartRoom;
			existingVerticesOfStartRoom = aMap.GetRoomVertices(start_room_type);
			

			//////////////////////////////////////////////////////////////////////////////
			// For each vertex of the current room check shorteset path to each
			for(int k=0; k<4; k++)
			{
				/////////////////////////////////////////////////////////////////////////
				// Vertex doesn't exist move on 

				if(existingVerticesOfStartRoom[k] == 0) continue;

				/////////////////////////////////////////////////////////////////////////
				// Otherwise consider this vertex.

				int current_vertex = verticesOfStartRoom[k];

				//////////////////////////////////////////////////////////////////////////////////////////////
				// Look at all blocks which havent been visited yet.

				for(unsigned int i=0; i<unknown_block_rooms.size(); i++)
				{			
					//////////////////////////////////////////////////////////////////////////////////////////
					// Find which of these vertices exist and their labels
					
					ERoom room_type = aMap.GetRoomType(unknown_block_rooms[i]);
					std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(unknown_block_rooms[i]);

					//////////////////////////////////////////////////////////////////////////////////////////
					// Check which of these vertices exist.

					std::vector<int> existingVerticesOfRoom;
					existingVerticesOfRoom = aMap.GetRoomVertices(room_type);
					std::vector<int> room_vertices = aMap.CalculateRoomVertices(unknown_block_rooms[i]);

					for(int j=0; j<4; j++)
					{
						if(existingVerticesOfRoom[j] == 0) continue;

						std::vector<int> current_shortest_path;
						int current_shortest_distance = aGraph.ShortestDistance(current_vertex, room_vertices[j], current_shortest_path);

						if(current_shortest_distance < shortest_distance)
						{
							shortest_distance = current_shortest_distance;
							shortest_path = current_shortest_path;
							start_vertex = current_vertex;
						}
					}
				}
			}

			planned_path = shortest_path;
		}
		else
		{
			/////////////////////////////////////////////////////////////////////////////////////////////
			// We know where we want to go next.

			int target_room = block_location[next_value];

			/////////////////////////////////////////////////////////////////////////////////////////////
			// Keep track of shortest distance and path and start vertex

			int start_vertex;
			double shortest_distance = LONG_MAX;
			std::vector<int> shortest_path;

			/////////////////////////////////////////////////////////////////////////////////////////////
			// Get current room type and the vertex labels of adjacent vertices.

			ERoom start_room_type = aMap.GetRoomType(current_room);
			std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(current_room);

			////////////////////////////////////////////////////////////////////////////////////////////
			// Check which of these vertices exist.

			std::vector<int> existingVerticesOfStartRoom;
			existingVerticesOfStartRoom = aMap.GetRoomVertices(start_room_type);


			///////////////////////////////////////////////////////////////////////////////////////
			// For each vertex of the current room check shortest path to vertex of room containing
			// the target block.

			for(int k=0; k<4; k++)
			{

				/////////////////////////////////////////////////////////////////////////
				// Vertex doesn't exist move on 
				if(existingVerticesOfStartRoom[k] == 0) continue;

				int current_vertex = verticesOfStartRoom[k];
			
				/////////////////////////////////////////////////////////////////////
				// Find which of these vertices exist and their labels

				ERoom room_type = aMap.GetRoomType(target_room);
				std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(target_room);

				/////////////////////////////////////////////////////////////////////////////
				// Check which of these vertices exist.

				std::vector<int> existingVerticesOfRoom;
				existingVerticesOfRoom = aMap.GetRoomVertices(room_type);
				std::vector<int> room_vertices = aMap.CalculateRoomVertices(target_room);

				for(int j=0; j<4; j++)
				{
					//////////////////////////////////////////////////////////////////////////////
					// Vertex doesnt exist

					if(existingVerticesOfRoom[j] == 0) continue;

					std::vector<int> current_shortest_path;
					int current_shortest_distance = aGraph.ShortestDistance(current_vertex, room_vertices[j], current_shortest_path);

					if(current_shortest_distance < shortest_distance)
					{
						shortest_distance = current_shortest_distance;
						shortest_path = current_shortest_path;
						start_vertex = current_vertex;
					}
				}

			}

			planned_path = shortest_path;

		}

		/////////////////////////////////////////////////////////////////////////////////////////////////
		// Compute macro instructions.

		CInstructions aInstructions = CInstructions(planned_path, 10);

		std::vector<EInstruction> macroInstructions = aInstructions.GetInstructions();


		//////////////////////////////////////////////////////////////////////////////////////////////
		// Now we know our route, execute it

		aMap.FollowInstructions(macroInstructions);
	}
	
	CGoodsOut::Stop();

	CSignals::Notification2();
}
