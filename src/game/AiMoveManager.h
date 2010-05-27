#pragma once

#include "Player.h"
#include "PlayerbotAI.h"
#include "AiManagerBase.h"
#include "AiTargetManager.h"

using namespace std;

namespace ai 
{
	class AiMoveManager : public AiManagerBase
	{
	public:
		AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual float GetDistanceTo(Unit* target);
		virtual void MoveTo(Unit* target, float distance = 0.0f);
		virtual float GetFollowAngle();
		virtual void Follow(Unit* target, float distance = 2.0f);
		virtual bool Flee(Unit* target, float distance = SPELL_DISTANCE);
		virtual void Stay();
		virtual bool IsMoving(Unit* target);
		virtual void Attack(Unit* target);
		virtual void ReleaseSpirit();
		virtual void Resurrect();
		virtual void Revive();
        virtual void Summon();
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
	};

};