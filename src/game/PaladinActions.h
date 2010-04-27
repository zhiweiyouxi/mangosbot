#pragma once
#include "PlayerbotAIFacade.h"
#include "GenericActions.h"

namespace ai
{
    class CastJudgementOfLightAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfLightAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "judgement of light") {}
    };

    class CastJudgementOfWisdomAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfWisdomAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "judgement of wisdom") {}
    };

    class CastJudgementOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfJusticeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "judgement of justice") {}
    };

    BEGIN_SPELL_ACTION(CastRighteousFuryAction, "righteous fury")
    END_SPELL_ACTION()

    // buffs
    BEGIN_SPELL_ACTION(CastDevotionAuraAction, "devotion aura")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRetributionAuraAction, "retribution aura")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastConcentrationAuraAction, "concentration aura")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastShadowResistanceAuraAction, "shadow resistance aura")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastFrostResistanceAuraAction, "frost resistance aura")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastFireResistanceAuraAction, "fire resistance aura")
    END_SPELL_ACTION()


    BEGIN_SPELL_ACTION(CastSealOfRighteousnessAction, "seal of righteousness")
    END_SPELL_ACTION()
    
    BEGIN_SPELL_ACTION(CastSealOfJusticeAction, "seal of justice")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSealOfLightAction, "seal of light")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSealOfWisdomAction, "seal of wisdom")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSealOfCommandAction, "seal of command")
    END_SPELL_ACTION()

    
    BEGIN_SPELL_ACTION(CastBlessingOfMightAction, "blessing of might")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastBlessingOfMightOnPartyAction, "blessing of might")
        virtual const char* getName() { return "blessing of might on party";}
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBlessingOfWisdomAction, "blessing of wisdom")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastBlessingOfWisdomOnPartyAction, "blessing of wisdom")
        virtual const char* getName() { return "blessing of wisdom on party";}
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBlessingOfKingsAction, "blessing of kings")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastBlessingOfKingsOnPartyAction, "blessing of kings")
        virtual const char* getName() { return "blessing of kings on party";}
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBlessingOfSanctuaryAction, "blessing of sanctuary")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastBlessingOfSanctuaryOnPartyAction, "blessing of sanctuary")
        virtual const char* getName() { return "blessing of sanctuary on party";}
    END_SPELL_ACTION()

    class CastHolyLightAction : public CastHealingSpellAction {
    public:
        CastHolyLightAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "holy light") {}
    };

    class CastHolyLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHolyLightOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "holy light") {}

        virtual const char* getName() { return "holy light on party"; }
    };

    class CastFlashOfLightAction : public CastHealingSpellAction {
    public:
        CastFlashOfLightAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "flash of light") {}
    };

    class CastFlashOfLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashOfLightOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "flash of light") {}

        virtual const char* getName() { return "flash of light on party"; }
    };

    class CastLayOnHandsAction : public CastHealingSpellAction {
    public:
        CastLayOnHandsAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "lay on hands") {}
    };

    class CastLayOnHandsOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLayOnHandsOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "lay on hands") {}

        virtual const char* getName() { return "lay on hands on party"; }
    };

    BEGIN_SPELL_ACTION(CastDivineProtectionAction, "divine protection")
    END_SPELL_ACTION()

    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "divine protection") {}

        virtual const char* getName() { return "divine protection on party"; }
    };

    BEGIN_SPELL_ACTION(CastDivineShieldAction, "divine shield")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastConsecrationAction, "consecration")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyWrathAction, "holy wrath")
    END_SPELL_ACTION()

    class CastJHammerOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastJHammerOfJusticeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

    BEGIN_SPELL_ACTION(CastPurifyAction, "purify")
    END_SPELL_ACTION()

    class CastPurifyOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}

        virtual const char* getName() { return "purify on party"; }
    };

    BEGIN_SPELL_ACTION(CastHandOfReckoningAction, "hand of reckoning")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCleanseAction, "cleanse")
    END_SPELL_ACTION()

    class CastCleanseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}

        virtual const char* getName() { return "cleanse on party"; }
    };

    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

}