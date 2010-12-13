#pragma once

using namespace std;

#define MAX_AI_MANAGER_TYPE 8

class Player;
class PlayerbotAI;

namespace ai 
{
    class AiManagerBase;
    
	class AiSpellManager;
	class AiTargetManager;
	class AiStatsManager;
	class AiMoveManager;
	class AiInventoryManager;
	class AiSocialManager;
	class AiQuestManager;
	class AiStrategyManager;
	class AiManagerBase;

	enum AiManagerType
	{
		AiSpellManagerType = 0,
		AiTargetManagerType = 1,
		AiStatsManagerType = 2,
		AiMoveManagerType = 3,
		AiInventoryManagerType = 4,
		AiSocialManagerType = 5,
		AiQuestManagerType = 6,
		AiStrategyManagerType = 7
	};

	class AiManagerRegistry
	{
	public:
		// for testing only
		AiManagerRegistry();
		AiManagerRegistry(PlayerbotAI* ai);
		virtual ~AiManagerRegistry();

	public:
		AiSpellManager* GetSpellManager() { return (AiSpellManager*)managers[AiSpellManagerType]; }
		AiTargetManager* GetTargetManager() { return (AiTargetManager*)managers[AiTargetManagerType]; }
		AiStatsManager* GetStatsManager() { return (AiStatsManager*)managers[AiStatsManagerType]; }
		AiMoveManager* GetMoveManager() { return (AiMoveManager*)managers[AiMoveManagerType]; }
		AiInventoryManager* GetInventoryManager() { return (AiInventoryManager*)managers[AiInventoryManagerType]; }
		AiSocialManager* GetSocialManager() { return (AiSocialManager*)managers[AiSocialManagerType]; }
		AiQuestManager* GetQuestManager() { return (AiQuestManager*)managers[AiQuestManagerType]; }
		AiStrategyManager* GetStrategyManager() { return (AiStrategyManager*)managers[AiStrategyManagerType]; }

		int GetManagerCount() { return MAX_AI_MANAGER_TYPE; }
		AiManagerBase** GetManagers() { return managers; }

	protected:
		AiManagerBase* managers[MAX_AI_MANAGER_TYPE];
	};

};