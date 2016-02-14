////////////////////////////////////////////////////////////////////////////////////////////////////
// Challenges.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Challenges.h"
#include "CMap.h"
#include "CGraph.h"
#include "Instructions.h"
#include "Signals.h"
#include "GoodsIn.h"
#include "GoodsOut.h"
#include "Manouvre.h"
#include <climits>

// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int LOCATION_UNKNOWN = -1;

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
	std::vector<int> labels;
	///////////////////////////// Call Johns Function to populate these


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Generate graph of map.

	CGraph aGraph = CGraph(distanceMatrix, labels);


	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Calculate shortest route from start to finish.


	std::vector<int> outputRoute;
	aGraph.ShortestDistance(entrance_vertex, exit_vertex, outputRoute);


	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute macro instructions.

	CInstructions aInstructions = CInstructions(outputRoute, 10);

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
	int start_vertex = aMap.GetEntranceVertex();

	///////////////////////////////////////////////////////////////////////
	// The value on the current block of interest.
	int next_value = 1;

	///////////////////////////////////////////////////////////////////////
	// Locations of blocks, the block with an image of one has its location
	// stored in the first entry, image of two in the second etc.
	// if unknown -1 or LOCATION UNKNOWN
	
	
	std::vector<int> block_location;
	block_location = {LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN, LOCATION_UNKNOWN};


	//////////////////////////////////////////////////////////////////////
	// Rooms containing blocks whose value is unknown.

	std::vector<int> unknown_block_rooms;
	aMap.CalculateBlockRooms(&unknown_block_rooms);

	/////////////////////////////////////////////////////////////////////
	// Rooms which contain a block. These may need 
	// to be revisited if we get an image wrong.

	std::vector<int> rooms_with_a_block;
	rooms_with_a_block = unknown_block_rooms;

	
	while(next_value <=5)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////
		// Create variable to hold next path.

		std::vector<int> planned_path;

		std::vector<std::vector<double>> distanceMatrix;
		std::vector<int> labels;


		// Calculated by Johns function.

		CGraph aGraph { distanceMatrix, labels };

		//////////////////////////////////////////////////////////////////////
		// Check if location of next block is known.

		if(block_location[next_value] == LOCATION_UNKNOWN)
		{
			

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
						double current_shortest_distance = aGraph.ShortestDistance(current_vertex, room_vertices[j], current_shortest_path);

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
			// Check which of these vertices exist for the start room.

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
					double current_shortest_distance = aGraph.ShortestDistance(current_vertex, room_vertices[j], current_shortest_path);

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

		//////////////////////////////////////////////////////////////////////////////////////////////
		// Now we know our route, execute it

		aMap.FollowInstructions(aInstructions);
	
	CGoodsOut::Stop();

	int current_block_number = CManouvre::ApproachAndPhotographBlock();

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Update the location vectors

	block_location[next_value] = current_block_number;



	if((current_block_number != next_value) && (block_location[next_value] != LOCATION_UNKNOWN))
	{
		////////////////////////////////////////////////////////////////////////////////////////
		// We have found a block we were not expecting. Reset all blocks that have not been removed
		// to unknown.

		unknown_block_rooms = rooms_with_a_block;
	}

	for(size_t i=0; i<unknown_block_rooms.size(); i++)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Remove the current room from the list of unknown rooms as we have just discovered which 
		// block is there.
		if(unknown_block_rooms[i] = current_room) 
		{
			unknown_block_rooms.erase(unknown_block_rooms.begin() + i);
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////
	// If the block is not the one we are currently interested continue.

	if(current_block_number != next_value)
	{
		CManouvre::ReverseAndUTurn();
		CSignals::Notification2();
		continue;
	}


	////////////////////////////////////////////////////////////////////////////////////
	// We are interested in this block collect it.

	CSignals::Notification3();

	CManouvre::CollectBlock();

	CManouvre::ReverseAndUTurn();

	///////////////////////////////////////////////////////////////////////////////////
	// Compute shortest path to start.

	std::vector<int> shortest_path;
	aGraph.ShortestDistance(aMap.GetCurrentVertex(), start_vertex, shortest_path);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute macro instructions.

	aInstructions = CInstructions(planned_path, 10);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Now we know our route, execute it

	aMap.FollowInstructions(aInstructions);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Exit map and release block.

	CManouvre::ExitMap();

	CManouvre::ReleaseBlock();

	CManouvre::ReverseAndUTurn();
	}

	CSignals::Complete();
}
