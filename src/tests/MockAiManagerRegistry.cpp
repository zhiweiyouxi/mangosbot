#include "pch.h"
#include "MockAiManagerRegistry.h"
#include "MockedTargets.h"

#include "AiManagerRegistry.h"

#include "AiStatsManager.h"
#include "AiSpellManager.h"
#include "AiTargetManager.h"
#include "AiMoveManager.h"
#include "AiInventoryManager.h"
#include "PlayerbotAIBase.h"
#include "MockAiStatsManager.h"
#include "MockAiSpellManager.h"
#include "MockAiTargetManager.h"
#include "MockAiMoveManager.h"
#include "MockAiInventoryManager.h"
#include "MockAiSocialManager.h"

using namespace std;
using namespace ai;

MockAiManagerRegistry::MockAiManagerRegistry() : AiManagerRegistry(&ai)
{
	if (spellManager) delete spellManager;
	if (statsManager) delete statsManager;
	if (targetManager) delete targetManager;
	if (moveManager) delete moveManager;
	if (inventoryManager) delete inventoryManager;
	if (socialManager) delete socialManager;

	statsManager = new MockAiStatsManager(&ai, this);
	spellManager = new MockAiSpellManager(&ai, this, &buffer);
	targetManager = new MockAiTargetManager(&ai, this);
	moveManager = new MockAiMoveManager(&ai, this, &buffer);
	inventoryManager = new MockAiInventoryManager(&ai, this, &buffer);
	socialManager = new MockAiSocialManager(&ai, this, &buffer);
}

MockAiManagerRegistry::~MockAiManagerRegistry()
{
}
