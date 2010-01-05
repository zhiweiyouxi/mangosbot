#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class TankWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        TankWarriorStrategy(PlayerbotAIFacade* const ai) : GenericWarriorStrategy(ai) {}

    public:
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "melee", 10.0f)
        END_NEXT_ACTIONS(1)
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "tank warrior"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}