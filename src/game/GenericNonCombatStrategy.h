#pragma once

#include "Strategy.h"
#include "ActionFactory.h"

namespace ai
{
    class GenericNonCombatStrategy : public Strategy
    {
    public:
        GenericNonCombatStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new ActionFactory(ai); }
    };

    class FollowMasterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        FollowMasterNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "follow"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class StayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        StayNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "stay"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class AssistNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        AssistNonCombatStrategy(PlayerbotAIFacade* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "assist"; }
        virtual ActionNode* createAction(const char* name);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}