#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericWarriorNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericWarriorNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "Warrior non combat"; }
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
    };
}