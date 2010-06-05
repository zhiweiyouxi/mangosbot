#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class DpsWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsWarriorStrategy(AiManagerRegistry* const ai) : GenericWarriorStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class WarriorBoostStrategy : public Strategy
    {
    public:
        WarriorBoostStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "boost"; }
    };
}