#include "pch.h"
#include "aitest.h"
#include "MockAiManagerRegistry.h"
#include "MockedTargets.h"

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
    managers[AiStrategyManagerType] = new MockAiStrategyManager(&ai, NULL, &buffer);
}

MockAiManagerRegistry::~MockAiManagerRegistry()
{
}
