#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class GenericMageNonCombatStrategy : public GenericMageStrategy
    {
    public:
        GenericMageNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericMageStrategy(ai) {}
        virtual const char* getName() { return "mage non combat"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };
}