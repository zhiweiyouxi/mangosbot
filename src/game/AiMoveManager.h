#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "AiTargetManager.h"

using namespace std;

namespace ai 
{
	class AiMoveManager : public AiManagerBase
	{
	public:
		AiMoveManager(PlayerbotAIBase* ai, AiTargetManager* targetManager, AiStatsManager* statsManager) : AiManagerBase(ai)
		{
			this->targetManager = targetManager;
			this->statsManager = statsManager;
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
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
	};

};