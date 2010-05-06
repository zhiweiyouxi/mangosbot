#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_SPELL_ACTION(CastDemonSkinAction, "demon skin")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDemonArmorAction, "demon armor")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastImmolateAction, "immolate")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDrainSoulAction, "drain soul")
		virtual bool isUseful() {
			return ai->GetItemCount("soulstone") < 2;
		}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDrainManaAction, "drain mana")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDrainLifeAction, "drain life")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastCurseOfAgonyAction, "curse of agony")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastCurseOfWeaknessAction, "curse of weakness")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastCorruptionAction, "corruption")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSummonVoidwalkerAction, "summon voidwalker")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSummonImpAction, "summon imp")
    END_SPELL_ACTION()
}