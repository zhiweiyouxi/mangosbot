#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericHunterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericHunterNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "hunter non combat"; }
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };
}