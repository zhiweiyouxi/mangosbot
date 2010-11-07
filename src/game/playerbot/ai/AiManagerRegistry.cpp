#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiManagers.h"


using namespace ai;
using namespace std;

AiManagerRegistry::AiManagerRegistry()
{
	for (int i=0; i<MAX_AI_MANAGER_TYPE; i++)
		managers[i] = NULL;
}

AiManagerRegistry::AiManagerRegistry(PlayerbotAI* ai) 
{
	managers[AiSpellManagerType] = new AiSpellManager(ai, this);
	managers[AiStatsManagerType] = new AiStatsManager(ai, this);
	managers[AiTargetManagerType] = new AiTargetManager(ai, this);
	managers[AiMoveManagerType] = new AiMoveManager(ai, this);
	managers[AiInventoryManagerType] = new AiInventoryManager(ai, this);
	managers[AiSocialManagerType] = new AiSocialManager(ai, this);
	managers[AiQuestManagerType] = new AiQuestManager(ai, this);
	managers[AiStrategyManagerType] = new AiStrategyManager(ai, this);
}

AiManagerRegistry::~AiManagerRegistry()
{
	for (int i=0; i<MAX_AI_MANAGER_TYPE; i++)
	{
		if (managers[i]) 
		{
			delete managers[i];
			managers[i] = NULL;
		}
	}
}
