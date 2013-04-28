#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ConserveManaStrategy.h"
#include "../../PlayerbotAIConfig.h"
#include "../actions/GenericSpellActions.h"
#include "../values/LastSpellCastValue.h"

using namespace ai;

float ConserveManaMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    uint8 health = AI_VALUE2(uint8, "health", "self target");
    uint8 targetHealth = AI_VALUE2(uint8, "health", "current target");
    uint8 mana = AI_VALUE2(uint8, "mana", "self target");
    bool hasMana = AI_VALUE2(bool, "has mana", "self target");
    bool mediumMana = hasMana && mana < sPlayerbotAIConfig.mediumMana;

    string name = action->getName();

    if (health < sPlayerbotAIConfig.lowHealth)
        return 1.0f;

    if (name == "melee" || name == "reach melee" || name == "reach spell")
        return 1.0f;

    if (mediumMana && dynamic_cast<CastBuffSpellAction*>(action))
        return 0.0f;

    if (action->GetTarget() != AI_VALUE(Unit*, "current target"))
        return 1.0f;

    if (AI_VALUE(uint8, "balance") <= 50)
        return 1.0f;

    if (targetHealth < sPlayerbotAIConfig.lowHealth && dynamic_cast<CastDebuffSpellAction*>(action))
        return 0.0f;

    if (mediumMana && dynamic_cast<CastDebuffSpellAction*>(action))
        return 0.0f;

    return 1.0f;
}

void ConserveManaStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new ConserveManaMultiplier(ai));
}

float SaveManaMultiplier::GetValue(Action* action)
{
    if (action == NULL)
        return 1.0f;

    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    string spell = spellAction->getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    const SpellEntry* const spellInfo = sSpellStore.LookupEntry(spellId);
    if (!spellInfo || spellInfo->powerType != POWER_MANA)
        return 1.0f;

    int32 cost = spellInfo->manaCost;
    if (spellInfo->ManaCostPercentage)
        cost += spellInfo->ManaCostPercentage * bot->GetCreateMana() / 100;

    uint32 mana = bot->GetMaxPower(POWER_MANA);
    double percent = (double)cost / (double)mana * 100.0f;

    time_t lastCastTime = AI_VALUE2(time_t, "last spell cast time", spell);
    if (!lastCastTime)
        return 1.0f;

    time_t elapsed = time(0) - lastCastTime;
    double k = 2.0;
    switch (bot->getClass())
    {
    case CLASS_HUNTER:
    case CLASS_SHAMAN:
    case CLASS_DRUID:
        k = 4.0;
        break;
    case CLASS_MAGE:
    case CLASS_PRIEST:
    case CLASS_WARLOCK:
        k = 2.0;
        break;
    default:
        k = 3.0;
    }
    if ((double)elapsed < 10 + pow(k, sqrt(percent)))
        return 0.0f;

    return 1.0f;
}

void SaveManaStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new SaveManaMultiplier(ai));
}
