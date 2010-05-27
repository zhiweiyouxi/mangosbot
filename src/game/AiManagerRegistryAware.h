#pragma once

#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "AiManagerRegistry.h"
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"
#include "AiStatsManager.h"
#include "AiInventoryManager.h"
#include "AiMoveManager.h"
#include "AiQuestManager.h"
#include "AiSocialManager.h"
#include "AiSpellManager.h"
#include "AiStatsManager.h"

namespace ai
{
    class AiManagerRegistryAware 
    {
    public:
        AiManagerRegistryAware(AiManagerRegistry* const ai) { this->ai = ai; }

    protected:
        AiManagerRegistry* ai;
    };
}