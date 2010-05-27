#include "pch.h"
#include "MockAiManagerRegistry.h"
#include "MockedTargets.h"

#include "AiManagerRegistry.h"

#include "AiStatsManager.h"
#include "AiSpellManager.h"
#include "AiTargetManager.h"
#include "AiMoveManager.h"
#include "AiInventoryManager.h"
#include "PlayerbotAI.h"
#include "MockAiStatsManager.h"
#include "MockAiSpellManager.h"
#include "MockAiTargetManager.h"
#include "MockAiMoveManager.h"
#include "MockAiInventoryManager.h"
#include "MockAiSocialManager.h"

using namespace std;
using namespace ai;

MockAiManagerRegistry::MockAiManagerRegistry() : AiManagerRegistry()
{
	managers[AiStatsManagerType] = new MockAiStatsManager(&ai, this);
	managers[AiSpellManagerType] = new MockAiSpellManager(&ai, this, &buffer);
	managers[AiTargetManagerType] = new MockAiTargetManager(&ai, this);
	managers[AiMoveManagerType] = new MockAiMoveManager(&ai, this, &buffer);
	managers[AiInventoryManagerType] = new MockAiInventoryManager(&ai, this, &buffer);
	managers[AiSocialManagerType] = new MockAiSocialManager(&ai, this, &buffer);
}

MockAiManagerRegistry::~MockAiManagerRegistry()
{
}
