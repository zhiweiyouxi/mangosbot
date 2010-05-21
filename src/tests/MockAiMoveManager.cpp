#include "pch.h"
#include "MockAiMoveManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

float MockAiMoveManager::GetDistanceTo(Unit* target)
{
	return distanceTo[target];
}

void MockAiMoveManager::MoveTo(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">master");

	if (target == MockedTargets::GetCurrentTarget())
	{
		if (distance == SPELL_DISTANCE) 
			buffer->append(">reach spell"); 
		else 
			buffer->append(">reach melee");
	}
}
float MockAiMoveManager::GetFollowAngle()
{
	return 0.0f;
}

void MockAiMoveManager::Follow(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">follow");
}

bool MockAiMoveManager::Flee(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">goaway");
	else
		buffer->append(">flee"); 

	return true;
}

void MockAiMoveManager::Stay()
{
	buffer->append(">stay");
}

bool MockAiMoveManager::IsMoving(Unit* target)
{
	return moving[target];
}
