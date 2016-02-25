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
#include "DebugLog.hpp"
#include "CMazeMapper.h"

// ~~~ DEFINITIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int LOCATION_UNKNOWN = -1;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Basic outline of challenge 1 I am not sure how the interupts will work exactly.
void CChallenges::ChallengeOne()
{
	DEBUG_METHOD();

	CSignals::Start();


	////////////////////////////////////////////////////////////////////////////////////////////////
	// Tell pic to follow line forever (or near enough) unless interrupted.

	CGoodsOut::Forward(INT_MAX, true);


	CGoodsOut::Stop();

	CSignals::Complete();
}

void CChallenges::ChallengeTwo()
{
	DEBUG_METHOD();


	//////////////////////////////////////////////////////////////////////
	// Create empty map

	CMap aMap = CMap(10, 10);

	///////////////////////////////////////////////////////////////////
	// Flag as to whether a vertex is needed.

	bool is_next_vertex;

	do{

		/////////////////////////////////////////////////////////////////////////////////
		// Find room type of current room and save it into the map.

		ERoom currentRoomType = CManouvre::DetectRoomType();
		aMap.SetCurrentRoomType(currentRoomType);


		///////////////////////////////////////////////////////////////////////////////
		// Find next route to explore. Create MazeMapper to choose next vertex and 
		// route to it.

		CMazeMapper aMazeMapper = CMazeMapper(&aMap);
		std::vector<int> outputRoute;
		is_next_vertex = aMazeMapper.ComputeNextVertex(aMap.GetCurrentVertex(), outputRoute);


		////////////////////////////////////////////////////////////////////////////////
		// If the next vertex was found move to next vertex.

		if(is_next_vertex)
		{
			CInstructions aInstructions = CInstructions(outputRoute, 10);
			aMap.FollowInstructions(aInstructions);  // Automatically updates aMap.m_nextRoom
		}

	}
	while(is_next_vertex);


	///////////////////////////////////////////////////////////////////////////////////////////
	// Map now completely known. Write to file.

	std::string filepath = "Data/ExportMap.txt";
	aMap.WriteCellMap(filepath);


	//////////////////////////////////////////////////////////////////////////////////////////
	// Signal function is complete.

	CSignals::Complete();
}

void CChallenges::ChallengeThree()
{
	DEBUG_METHOD();
	std::string filepath;

	filepath = std::string("TestData/PracticeMap.csv");

	CMap aMap = CMap(filepath);
	int entrance_vertex = aMap.GetEntranceVertex();
	int exit_vertex = aMap.GetExitVertex();

	std::vector<std::vector<double>> distanceMatrix = aMap.DistanceMatrix();

	///////////////////////////////////////////////////////////////
	CGraph aGraph = CGraph(distanceMatrix);


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

	// TODO: NB the CMap member variables tracking the location are not updated here!!!
	// If you decide you need to use them, then the easiest way would be to use the CMap::FollowInstructions method.
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
	DEBUG_METHOD();
	///////////////////////////////////////////////////////////////////////
	// Import map
	std::string filepath = "TestData/PracticeMap_WithBlocks.csv";
	CMap aMap = CMap(filepath);


	////////////////////////////////////////////////////////////////////////
	// Set the current room as the starting room of the map.
//	int current_room = aMap.GetEntranceRoom();

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
	
	
	int LOCATION_UNKNOWN = -1;
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

		std::vector<std::vector<double>> distanceMatrix = aMap.DistanceMatrix();

		///////////////////////////////////////////////////////////////
		CGraph aGraph = CGraph(distanceMatrix);


		//////////////////////////////////////////////////////////////////////
		// Check if location of next block is known.

		if(block_location[next_value] == LOCATION_UNKNOWN)
		{

			//////////////////////////////////////////////////////////////////////////////////
			// Keep track of shortest distance and path and start vertex

			int start_vertex;
			double shortest_distance = LONG_MAX;
			std::vector<int> shortest_path;
			bool end_straight = false;

			//////////////////////////////////////////////////////////////////////
			// Get current room type and the vertex labels of adjacent vertices.

			ERoom start_room_type = aMap.GetRoomType(aMap.GetNextRoom());
			std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(aMap.GetNextRoom());


			/////////////////////////////////////////////////////////////////////////////
			// Check which of these vertices exist.

			std::vector<int> existingVerticesOfStartRoom;
			existingVerticesOfStartRoom = aMap.GetRoomVertices(start_room_type);
			

			//////////////////////////////////////////////////////////////////////////////
			// For each vertex of the current room check shortest path to each
			for(int k=0; k<4; k++)
			{
				/////////////////////////////////////////////////////////////////////////
				// Vertex doesn't exist move on 

				if(existingVerticesOfStartRoom[k] == 0) continue;

				/////////////////////////////////////////////////////////////////////////
				// Otherwise consider this vertex.

				int current_vertex = verticesOfStartRoom[k];

				//////////////////////////////////////////////////////////////////////////////////////////////
				// Look at all blocks which haven't been visited yet.

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

						int size = current_shortest_path.size();
						CInstructions aInstructions = CInstructions({current_shortest_path[size -2], current_shortest_path[size -1]}, 10);
						std::vector<EInstruction> instruction = aInstructions.GetInstructions();

						bool replace = false;

						if(current_shortest_distance < shortest_distance)
						{
							if(!end_straight) replace = true;
							else if(instruction[0] == EInstruction_Straight) replace = true;
						}
						else if(!end_straight && (instruction[0] == EInstruction_Straight)) replace = true;

						if(replace)
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
			bool end_straight = false;

			/////////////////////////////////////////////////////////////////////////////////////////////
			// Get current room type and the vertex labels of adjacent vertices.

			ERoom start_room_type = aMap.GetRoomType(aMap.GetNextRoom());
			std::vector<int> verticesOfStartRoom = aMap.CalculateRoomVertices(aMap.GetNextRoom());

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
					
					int size = current_shortest_path.size();
					CInstructions aInstructions = CInstructions({current_shortest_path[size -2], current_shortest_path[size -1]}, 10);
					std::vector<EInstruction> instruction = aInstructions.GetInstructions();

					bool replace = false;

					if(current_shortest_distance < shortest_distance)
					{
						if(!end_straight) replace = true;
						else if(instruction[0] == EInstruction_Straight) replace = true;
					}
					else if(!end_straight && (instruction[0] == EInstruction_Straight)) replace = true;

					if(replace)
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


		aMap.FollowInstructionsNotLast(aInstructions); // Automatically updates aMap.m_nextRoom


	
	CGoodsOut::Stop();

	// TODO: We need to sort out how exacty to split up the approach here...
	// E.g. ApproachBlock (passing last instruction)
	//      Create a CBlockReader (default constructor) and TakePhoto() (pass a filepath if we want to keep the photo)
	//      Call the CountSpotsMethod
	// In particular here, the taking of the photo is separate from the approach.
	// So we kill two birds with one stone and don't need to rephotograph known blocks before we collect them.
	int current_block_number = CManouvre::ApproachAndPhotographBlock(); // Do not manually update aMap.m_nextRoom

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Update the location vectors
	//***************************************************
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
		if(unknown_block_rooms[i] == aMap.GetNextRoom())
		{
			unknown_block_rooms.erase(unknown_block_rooms.begin() + i);
		}
	}
	
	for(size_t i=0; i<unknown_block_rooms.size(); i++) // TODO: Did you really want this twice??
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Remove the current room from the list of unknown rooms as we have just discovered which 
		// block is there.
		if(unknown_block_rooms[i] == aMap.GetNextRoom())
		{
			unknown_block_rooms.erase(unknown_block_rooms.begin() + i);
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////
	// If the block is not the one we are currently interested continue.

	if(current_block_number != next_value)
	{
		CSignals::Notification2();
		CManouvre::ReverseAndUTurn();
		aMap.SetNextRoom(); // TODO: Must manually update aMap.m_nextRoom and m_currnetOrientation (but maybe not m_currentVertex?) after ReverseAndUTurn
		continue;
	}


	////////////////////////////////////////////////////////////////////////////////////
	// We are interested in this block collect it.

	CSignals::Notification3();

	CManouvre::CollectBlock();

	// TODO: If we are collecting the block then the shortest distance isn't necessarily from the vertex we came (though due to time pressures I don't suggest you change it!)
	CManouvre::ReverseAndUTurn();
	aMap.SetNextRoom(); // TODO: Must manually update aMap.m_nextRoom and m_currnetOrientation (but maybe not m_currentVertex?) after ReverseAndUTurn

	///////////////////////////////////////////////////////////////////////////////////
	// Compute shortest path to start.

	std::vector<int> shortest_path;
	aGraph.ShortestDistance(aMap.GetCurrentVertex(), start_vertex, shortest_path);

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute macro instructions.

	aInstructions = CInstructions(planned_path, 10);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Now we know our route, execute it

	aMap.FollowInstructions(aInstructions); // Automatically updates aMap.m_nextRoom

	////////////////////////////////////////////////////////////////////////////////////////////
	// Exit map and release block.

	CManouvre::ExitMap();

	CManouvre::ReleaseBlock();

	CManouvre::ReverseAndUTurn();
	aMap.SetNextRoom(); // TODO: Must manually update aMap.m_nextRoom and m_currnetOrientation (but maybe not m_currentVertex?) after ReverseAndUTurn

	}

	CSignals::Complete();
}
