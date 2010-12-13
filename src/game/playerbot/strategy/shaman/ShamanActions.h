#pragma once

#include "../GenericActions.h"

namespace ai
{
    class CastLesserHealingWaveAction : public CastHealingSpellAction {
    public:
        CastLesserHealingWaveAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "lesser healing wave") {}
    };

    class CastLesserHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealingWaveOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "lesser healing wave") {}
    };


    class CastHealingWaveAction : public CastHealingSpellAction {
    public:
        CastHealingWaveAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "healing wave") {}
    };

    class CastHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingWaveOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "healing wave") {}
    };

    class CastChainHealAction : public CastHealingSpellAction {
    public:
        CastChainHealAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "chain heal") {}
    };

    class CastChainHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastChainHealOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "chain heal") {}
    };

    class CastRiptideAction : public CastHealingSpellAction {
    public:
        CastRiptideAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "riptide") {}
    };

    class CastRiptideOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRiptideOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "riptide") {}
    };


    class CastEarthShieldAction : public CastBuffSpellAction {
    public:
        CastEarthShieldAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "earth shield") {}
    };

    class CastEarthShieldOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastEarthShieldOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "earth shield") {}
    };

    class CastWaterShieldAction : public CastBuffSpellAction {
    public:
        CastWaterShieldAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "water shield") {}
    };


    class CastEarthlivingWeaponAction : public CastBuffSpellAction {
    public:
        CastEarthlivingWeaponAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "earthliving weapon") {}
    };

    class CastRockbiterWeaponAction : public CastBuffSpellAction {
    public:
        CastRockbiterWeaponAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "rockbiter weapon") {}
    };

    class CastFlametongueWeaponAction : public CastBuffSpellAction {
    public:
        CastFlametongueWeaponAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "flametongue weapon") {}
    };

    class CastFrostbrandWeaponAction : public CastBuffSpellAction {
    public:
        CastFrostbrandWeaponAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "frostbrand weapon") {}
    };

    class CastWindfuryWeaponAction : public CastBuffSpellAction {
    public:
        CastWindfuryWeaponAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "windfury weapon") {}
    };

    class CastStoneskinTotemAction : public CastBuffSpellAction {
    public:
        CastStoneskinTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "stoneskin totem") {}
    };

    class CastEarthbindTotemAction : public CastBuffSpellAction {
    public:
        CastEarthbindTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "earthbind totem") {}
    };

    class CastStrengthOfEarthTotemAction : public CastBuffSpellAction {
    public:
        CastStrengthOfEarthTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "strength of earth totem") {}
    };

    class CastManaSpringTotemAction : public CastBuffSpellAction {
    public:
        CastManaSpringTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "mana spring totem") {}
    };

    class CastCleansingTotemAction : public CastBuffSpellAction {
    public:
        CastCleansingTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "cleansing totem") {}
    };

    class CastFlametongueTotemAction : public CastBuffSpellAction {
    public:
        CastFlametongueTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "flametongue totem") {}
    };

    class CastWindfuryTotemAction : public CastBuffSpellAction {
    public:
        CastWindfuryTotemAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "windfury totem") {}
    };

    class CastWindShearAction : public CastSpellAction {
    public:
        CastWindShearAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "wind shear") {}
    };

	class CastAncestralSpiritAction : public ResurrectPartyMemberAction
	{
	public:
		CastAncestralSpiritAction(AiManagerRegistry* const ai) : ResurrectPartyMemberAction(ai, "ancestral spirit") {}
	};
    
}