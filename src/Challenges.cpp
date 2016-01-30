////////////////////////////////////////////////////////////////////////////////////////////////////
// Challenges.cpp
// Created: 15/11/15
// Author: Hannah Howell
//

#include "Challenges.h"
#include "Signals.h"
#include "GoodsIn.h"
#include "GoodsOut.h"
#include <climits>

void CChallenges::ChallengeOne()
{
	CSignals::Start();

	bool interrupt = false;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Tell pic to follow line forever (or near enough) unless interrupted.

	CGoodsOut::Forward(LLONG_MAX, true);

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

void CChallenges::ChallengeTwo()
{

}

void CChallenges::ChallengeThree()
{

}

void CChallenges::ChallengeFour()
{

}
