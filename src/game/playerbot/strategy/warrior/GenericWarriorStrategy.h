#pragma once

#include "../Strategy.h"

namespace ai
{
    class ActionFactory;

    class GenericWarriorStrategy : public CombatStrategy
    {
    public:
        GenericWarriorStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory();
        virtual const char* getName() { return "warrior"; }
        ActionNode* createAction(const char* name);
    };
}