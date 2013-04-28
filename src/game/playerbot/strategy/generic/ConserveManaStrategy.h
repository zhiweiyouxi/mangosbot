#pragma once

namespace ai
{
    class ConserveManaMultiplier : public Multiplier
    {
    public:
        ConserveManaMultiplier(PlayerbotAI* ai) : Multiplier(ai, "conserve mana") {}

    public:
        virtual float GetValue(Action* action);
    };

    class ConserveManaStrategy : public Strategy
    {
    public:
        ConserveManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "conserve mana"; }
    };

    class SaveManaMultiplier : public Multiplier
    {
    public:
        SaveManaMultiplier(PlayerbotAI* ai) : Multiplier(ai, "save mana") {}

    public:
        virtual float GetValue(Action* action);
    };

    class SaveManaStrategy : public Strategy
    {
    public:
        SaveManaStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    public:
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual string getName() { return "save mana"; }
    };


}
