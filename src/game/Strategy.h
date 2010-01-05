#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"

namespace ai
{
    class Strategy : public PlayerbotAIFacadeAware
    {
    public:
        Strategy(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~Strategy() {}

    public:
        virtual NextAction** getDefaultActions() { return NULL; }
        virtual void InitTriggers(std::list<TriggerNode*> &triggers) {}
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers) {}
        virtual const char* getName() = NULL;
        virtual ActionNode* createAction(const char* name)  { return NULL; }
    };

    class CombatStrategy : public Strategy
    {
    public:
        CombatStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
