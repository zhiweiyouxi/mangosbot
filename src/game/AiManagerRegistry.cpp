#include "pchdef.h"
#include "AiManagerRegistry.h"
#include "MotionMaster.h"
#include "FleeManager.h"
#include "AiSpellManager.h"
#include "AiStatsManager.h"
#include "AiTargetManager.h"
#include "AiInventoryManager.h"
#include "AiMoveManager.h"

using namespace ai;
using namespace std;

AiManagerRegistry::AiManagerRegistry(PlayerbotAIBase* ai) 
{
	spellManager = new AiSpellManager(ai, this);
	statsManager = new AiStatsManager(ai, this);
	targetManager = new AiTargetManager(ai, this);
	moveManager = new AiMoveManager(ai, this);
	inventoryManager = new AiInventoryManager(ai, this);
	socialManager = new AiSocialManager(ai, this);
}

AiManagerRegistry::~AiManagerRegistry()
{
	if (spellManager) delete spellManager;
	if (statsManager) delete statsManager;
	if (targetManager) delete targetManager;
	if (moveManager) delete moveManager;
	if (inventoryManager) delete inventoryManager;
	if (socialManager) delete socialManager;
}
