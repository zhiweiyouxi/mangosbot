#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class TankWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        TankWarriorStrategy(AiManagerRegistry* const ai) : GenericWarriorStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "tank"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}