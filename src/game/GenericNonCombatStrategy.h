#pragma once

#include "Strategy.h"
#include "ActionFactory.h"

namespace ai
{
    class GenericNonCombatStrategy : public Strategy
    {
    public:
        GenericNonCombatStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    };

    class FollowMasterNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        FollowMasterNonCombatStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "follow"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class GoAwayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        GoAwayNonCombatStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "goaway"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class StayNonCombatStrategy : public GenericNonCombatStrategy
    {
    public:
        StayNonCombatStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "stay"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };

    class DpsAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        DpsAssistStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "dps assist"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class TankAssistStrategy : public GenericNonCombatStrategy
    {
    public:
        TankAssistStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
        virtual const char* getName() { return "tank non combat"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class LootNonCombatStrategy : public Strategy
    {
    public:
        LootNonCombatStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "loot"; }
    };

    class RandomEmoteStrategy : public Strategy
    {
    public:
        RandomEmoteStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "emote"; }
        virtual ActionNode* createAction(const char* name);
   };

    class PassiveStrategy : public Strategy
    {
    public:
        PassiveStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "passive"; }
    };

    class LowManaStrategy : public Strategy
    {
    public:
        LowManaStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "low mana"; }
    };

    class UseFoodStrategy : public Strategy
    {
    public:
        UseFoodStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "food"; }
    };
}