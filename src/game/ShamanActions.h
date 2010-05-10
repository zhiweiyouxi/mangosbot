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

        virtual const char* getName() { return "lesser healing wave on party"; }
    };


    class CastHealingWaveAction : public CastHealingSpellAction {
    public:
        CastHealingWaveAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "healing wave") {}
    };

    class CastHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingWaveOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "healing wave") {}

        virtual const char* getName() { return "healing wave on party"; }
    };

    class CastChainHealAction : public CastHealingSpellAction {
    public:
        CastChainHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "chain heal") {}
    };

    class CastChainHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastChainHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "chain heal") {}

        virtual const char* getName() { return "chain heal on party"; }
    };

    class CastRiptideAction : public CastHealingSpellAction {
    public:
        CastRiptideAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "riptide") {}
    };

    class CastRiptideOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRiptideOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "riptide") {}

        virtual const char* getName() { return "riptide on party"; }
    };


    class CastEarthShieldAction : public CastHealingSpellAction {
    public:
        CastEarthShieldAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "earth shield") {}
    };

    class CastEarthShieldOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastEarthShieldOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "earth shield") {}

        virtual const char* getName() { return "earth shield on party"; }
    };

    class CastWaterShieldAction : public CastSpellAction {
    public:
        CastWaterShieldAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "water shield") {}
    };


    class CastEarthlivingWeaponAction : public CastSpellAction {
    public:
        CastEarthlivingWeaponAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "earthliving weapon") {}
    };
    

    class CastStoneskinTotemAction : public CastSpellAction {
    public:
        CastStoneskinTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "stoneskin totem") {}
    };

    class CastEarthbindTotemAction : public CastSpellAction {
    public:
        CastEarthbindTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "earthbind totem") {}
    };

    class CastStrengthOfEarthTotemAction : public CastSpellAction {
    public:
        CastStrengthOfEarthTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "strength of earth totem") {}
    };

    class CastManaSpringTotemAction : public CastSpellAction {
    public:
        CastManaSpringTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "mana spring totem") {}
    };

    class CastCleansingTotemAction : public CastSpellAction {
    public:
        CastCleansingTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "cleansing totem") {}
    };

    class CastFlametongueTotemAction : public CastSpellAction {
    public:
        CastFlametongueTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "flametongue totem") {}
    };

    class CastWindfuryTotemAction : public CastSpellAction {
    public:
        CastWindfuryTotemAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "windfury totem") {}
    };

    class CastWindShearAction : public CastSpellAction {
    public:
        CastWindShearAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "wind shear") {}
    };
    
}