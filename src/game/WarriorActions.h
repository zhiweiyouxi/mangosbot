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

    BEGIN_MELEE_SPELL_ACTION(CastExecuteAction, "execute")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastOverpowerAction, "overpower")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastHamstringAction, "hamstring")
    END_SPELL_ACTION()

    class CastTauntAction : public CastRangedSpellAction {
    public:
        CastTauntAction(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, "taunt") {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastRangedSpellAction::getPrerequisites());
        }
    };

    // after dodge
    BEGIN_MELEE_SPELL_ACTION(CastRevengeAction, "revenge")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastSunderArmorAction, "sunder armor") // 5 times
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastDemoralizingShoutAction, "demoralizing shout")
    END_SPELL_ACTION()

    // stuns
    BEGIN_MELEE_SPELL_ACTION(CastShieldBashAction, "shield bash")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    END_SPELL_ACTION()

    // buffs
    BEGIN_SPELL_ACTION(CastBattleShoutAction, "battle shout")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDefensiveStanceAction, "defensive stance")
        virtual BOOL isUseful() {
            return CastSpellAction::isUseful() && !ai->HasAura("defensive stance");
        }
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBattleStanceAction, "battle stance")
    virtual BOOL isUseful() {
        return CastSpellAction::isUseful() && !ai->HasAura("battle stance");
    }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastChargeAction, "charge")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDeathWishAction, "death wish")
    END_SPELL_ACTION()   

    BEGIN_SPELL_ACTION(CastBerserkerRageAction, "berserker rage")
    END_SPELL_ACTION()   
}