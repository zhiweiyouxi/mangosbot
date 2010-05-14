#pragma once

#include "Strategy.h"

namespace ai
{
    class DpsRogueStrategy : public CombatStrategy
    {
    public:
        DpsRogueStrategy(PlayerbotAIFacade* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "cat"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}