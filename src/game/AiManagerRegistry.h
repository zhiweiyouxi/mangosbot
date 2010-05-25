#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"

using namespace std;

namespace ai 
{
	class AiSpellManager;
	class AiTargetManager;
	class AiStatsManager;
	class AiMoveManager;

	class AiManagerRegistry
	{
	public:
		AiManagerRegistry(PlayerbotAIBase* ai);
		virtual ~AiManagerRegistry();

	public:
		AiSpellManager* GetSpellManager() { return spellManager; }
		AiTargetManager* GetTargetManager() { return targetManager; }
		AiStatsManager* GetStatsManager() { return statsManager; }
		AiMoveManager* GetMoveManager() { return moveManager; }

	protected:
		AiSpellManager* spellManager;
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
		AiMoveManager* moveManager;
	};

};