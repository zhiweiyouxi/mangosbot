#pragma once

#include "../Strategy.h"

namespace ai
{
    class GenericMageStrategy : public CombatStrategy
    {
    public:
        GenericMageStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}
        virtual const char* getName() { return "mage"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };

    class MageBoostStrategy : public Strategy
    {
    public:
        MageBoostStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "boost"; }
    };
}