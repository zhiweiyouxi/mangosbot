#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericWarlockNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "warlock non combat"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };
}