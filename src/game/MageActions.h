#pragma once

#include "Action.h"

namespace ai
{
    class CastFrostBoltAction : public CastSpellAction
    {
    public:
        CastFrostBoltAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "frostbolt") {}
        virtual NextAction* getNextAction() { return new NextAction("frostbolt", 1.0f); }
    };

    //------------------------------------------------------------------------------------------

    class CastFrostNovaAction : public CastSpellAction
    {
    public:
        CastFrostNovaAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "frost nova") {}
        virtual NextAction* getNextAction() { return new NextAction("flee", 10.0f); }
    };
}