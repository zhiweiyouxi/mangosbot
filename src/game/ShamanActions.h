#pragma once

#include "GenericActions.h"

namespace ai
{
    class CastLesserHealingWaveAction : public CastHealingSpellAction {
    public:
        CastLesserHealingWaveAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "lesser healing wave") {}
    };

    class CastLesserHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealingWaveOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "lesser healing wave") {}
    };


    class CastHealingWaveAction : public CastHealingSpellAction {
    public:
        CastHealingWaveAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "healing wave") {}
    };

    class CastHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingWaveOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "healing wave") {}
    };

    class CastChainHealAction : public CastHealingSpellAction {
    public:
        CastChainHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "chain heal") {}
    };

    class CastChainHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastChainHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "chain heal") {}
    };

    class CastRiptideAction : public CastHealingSpellAction {
    public:
        CastRiptideAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "riptide") {}
    };

    class CastRiptideOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRiptideOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "riptide") {}
    };


    class CastEarthShieldAction : public CastBuffSpellAction {
    public:
        CastEarthShieldAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "earth shield") {}
    };

    class CastEarthShieldOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastEarthShieldOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "earth shield") {}
    };

    class CastWaterShieldAction : public CastBuffSpellAction {
    public:
        CastWaterShieldAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "water shield") {}
    };


    class CastEarthlivingWeaponAction : public CastBuffSpellAction {
    public:
        CastEarthlivingWeaponAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "earthliving weapon") {}
    };
    

    class CastStoneskinTotemAction : public CastBuffSpellAction {
    public:
        CastStoneskinTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "stoneskin totem") {}
    };

    class CastEarthbindTotemAction : public CastBuffSpellAction {
    public:
        CastEarthbindTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "earthbind totem") {}
    };

    class CastStrengthOfEarthTotemAction : public CastBuffSpellAction {
    public:
        CastStrengthOfEarthTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "strength of earth totem") {}
    };

    class CastManaSpringTotemAction : public CastBuffSpellAction {
    public:
        CastManaSpringTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "mana spring totem") {}
    };

    class CastCleansingTotemAction : public CastBuffSpellAction {
    public:
        CastCleansingTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "cleansing totem") {}
    };

    class CastFlametongueTotemAction : public CastBuffSpellAction {
    public:
        CastFlametongueTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "flametongue totem") {}
    };

    class CastWindfuryTotemAction : public CastBuffSpellAction {
    public:
        CastWindfuryTotemAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "windfury totem") {}
    };

    class CastWindShearAction : public CastSpellAction {
    public:
        CastWindShearAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "wind shear") {}
    };

	class CastAncestralSpiritAction : public ResurrectPartyMemberAction
	{
	public:
		CastAncestralSpiritAction(PlayerbotAIFacade* const ai) : ResurrectPartyMemberAction(ai, "ancestral spirit") {}
	};
    
}