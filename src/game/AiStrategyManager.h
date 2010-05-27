#ifndef _PLAYERBOTCLASSAI_H
#define _PLAYERBOTCLASSAI_H

#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"
#include "PlayerbotAI.h"

#include "Engine.h"
#include "AiManagerRegistry.h"

#include "Engine.h"

using namespace ai;
using namespace std;


namespace ai
{
	class AiManagerRegistry;

	class AiStrategyManager : public AiManagerBase
	{
	public:
		AiStrategyManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);
		virtual ~AiStrategyManager();

	public:
		virtual void DoNextAction();
		virtual void DoSpecificAction(const char* name);
		virtual void ChangeStrategy( const char* name, Engine* e );
		virtual void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, combatEngine); }
		virtual void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	protected:
		Engine* currentEngine;
		Engine* combatEngine;
		Engine* nonCombatEngine;
	};

}
#endif
