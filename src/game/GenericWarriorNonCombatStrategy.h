#pragma once

#include "GenericNonCombatStrategy.h"

namespace ai
{
    class GenericWarriorNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GenericWarriorNonCombatStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "nc"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
   };
}