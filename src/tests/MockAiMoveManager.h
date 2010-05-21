#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiMoveManager.h"
#include "AiTargetManager.h"

namespace ai
{
    class MockAiMoveManager : public AiMoveManager
    {
    public:
        MockAiMoveManager(PlayerbotAIBase* ai, AiTargetManager* targetManager, string *buffer) : AiMoveManager(ai, targetManager) 
        {
			distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f; 
			moving[MockedTargets::GetCurrentTarget()] = false;
			this->buffer = buffer;
		}

	public:
		virtual float GetDistanceTo(Unit* target);
		virtual void MoveTo(Unit* target, float distance = 0.0f);
		virtual float GetFollowAngle();
		virtual void Follow(Unit* target, float distance = 2.0f);
		virtual bool Flee(Unit* target, float distance = SPELL_DISTANCE);
		virtual void Stay();
		virtual bool IsMoving(Unit* target);

	private:
		string *buffer;

	public:
		map<Unit*, float> distanceTo;
		map<Unit*, bool> moving;
    };

}