#pragma once

#include "../Strategy.h"

namespace ai
{
    class ActionFactory;

    class GenericDruidStrategy : public CombatStrategy
    {
    protected:
        GenericDruidStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory();
        virtual ActionNode* createAction(const char* name);
    };

    class DruidBoostStrategy : public Strategy
    {
    public:
        DruidBoostStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "boost"; }
    };
}