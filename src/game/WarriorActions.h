#pragma once

#include "GenericActions.h"

namespace ai
{
    // main
    BEGIN_MELEE_SPELL_ACTION(CastHeroicStrikeAction, "heroic strike")
    END_SPELL_ACTION()

    // attack me
    BEGIN_MELEE_SPELL_ACTION(CastMockingBlowAction, "mocking blow")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastTauntAction, "taunt")
    END_SPELL_ACTION()

    // after dodge
    BEGIN_MELEE_SPELL_ACTION(CastRevengeAction, "revenge")
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastSunderArmorAction, "sunder armor") // 5 times
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDemoralizingShoutAction, "demoralizing shout")
    END_SPELL_ACTION()

    // stuns
    BEGIN_SPELL_ACTION(CastShieldBashAction, "shield bash")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    END_SPELL_ACTION()

    // buffs
    BEGIN_SPELL_ACTION(CastBattleShoutAction, "battle shout")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDefensiveStanceAction, "defensive stance")
    END_SPELL_ACTION()

}