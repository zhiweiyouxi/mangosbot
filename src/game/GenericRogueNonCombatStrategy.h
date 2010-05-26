#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericRogueNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericRogueNonCombatStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };
}