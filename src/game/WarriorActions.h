#pragma once

#include "GenericActions.h"

#define DEFAULT_WARRIOR_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(1) \
    NEXT_ACTION(0, "melee", 10.0f) \
    END_NEXT_ACTIONS(1)

namespace ai
{
    // main
    BEGIN_SPELL_ACTION(CastHeroicStrikeAction, "heroic strike")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    // attack me
    BEGIN_SPELL_ACTION(CastMockingBlowAction, "mocking blow")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    ALTERNATIVE_ACTIONS("taunt")
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastTauntAction, "taunt")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    // after dodge
    BEGIN_SPELL_ACTION(CastRevengeAction, "revenge")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    ALTERNATIVE_ACTIONS("melee")
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastSunderArmorAction, "sunder armor") // 5 times
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDemoralizingShoutAction, "demoralizing shout")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    // stuns
    BEGIN_SPELL_ACTION(CastShieldBashAction, "shield bash")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    // buffs
    BEGIN_SPELL_ACTION(CastBattleShoutAction, "battle shout")
    DEFAULT_WARRIOR_NEXT_ACTIONS()
    PREREQUISITE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDefensiveStanceAction, "defensive stance")
    END_SPELL_ACTION()

}