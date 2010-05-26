#pragma once

#include "AiManagerRegistry.h"
#include "PlayerbotAI.h"
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"

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