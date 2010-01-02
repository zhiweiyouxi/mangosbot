#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "druid non combat"; }
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
    };
}