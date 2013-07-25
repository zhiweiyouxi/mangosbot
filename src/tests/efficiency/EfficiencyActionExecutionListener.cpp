#include "pch.h"
#include "../aitest.h"
#include "../EngineTestBase.h"
#include "../MockedTargets.h"
#include "../AiObjectContextWrapper.h"
#include "EfficiencyActionExecutionListener.h"


EfficiencyActionExecutionListener::EfficiencyActionExecutionListener(MockPlayerbotAIBase *ai, map<string, SpellInfo> spellInfo, double mana) :
    ai(ai), spellInfo(spellInfo), mana(mana), castTime(0), damage(0)
{
}

bool EfficiencyActionExecutionListener::Before(Action* action, Event event)
{
    return true;
}

bool EfficiencyActionExecutionListener::AllowExecution(Action* action, Event event)
{
    return false;
}

bool EfficiencyActionExecutionListener::OverrideResult(Action* action, bool executed, Event event)
{
    if (!executed)
        return false;

    string name = action->getName();
    if (!spellInfo.count(name))
        return false;

    SpellInfo spell = spellInfo[name];

    if (cooldown.count(name) && cooldown[name] > 0)
    {
        cout << name << " is on cooldown" << endl;
        return false;
    }

    if (mana < spell.mana)
    {
        cout << name << ": OOM" << endl;
        return false;
    }

    cout << name << endl;
    return true;
}

void EfficiencyActionExecutionListener::After(Action* action, bool executed, Event event)
{
    if (!executed)
        return;

    string name = action->getName();
    if (!spellInfo.count(name))
        return;

    SpellInfo spell = spellInfo[name];

    for (map<string, double>::iterator i = cooldown.begin(); i != cooldown.end(); ++i)
    {
        int value = i->second - spell.castTime;
        cooldown[i->first] = value > 0 ? value : 0;
    }

    if (spell.castTime > 1.5)
        castTime += spell.castTime;
    else
        castTime += 1.5;
    mana -= spell.mana;
    cooldown[name] = spell.cooldown;
    damage += spell.damage;
}

void EfficiencyActionExecutionListener::Report()
{
    cout << "Time: " << castTime << endl <<
            "Damage: " << damage << endl <<
            "Mana: " << mana << endl;
    if (damage > 0 && castTime > 0)
        cout << "DPS: " << damage / castTime << endl;
}
