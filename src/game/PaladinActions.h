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

	class CastRighteousFuryAction : public CastBuffSpellAction {
	public:
		CastRighteousFuryAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "righteous fury") {}
	};

	class CastDevotionAuraAction : public CastBuffSpellAction {
	public:
		CastDevotionAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "devotion aura") {}
	};

	class CastRetributionAuraAction : public CastBuffSpellAction {
	public:
		CastRetributionAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "retribution aura") {}
	};

	class CastConcentrationAuraAction : public CastBuffSpellAction {
	public:
		CastConcentrationAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "concentration aura") {}
	};

	class CastShadowResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastShadowResistanceAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "shadow resistance aura") {}
	};

	class CastFrostResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFrostResistanceAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "frost resistance aura") {}
	};

	class CastFireResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFireResistanceAuraAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "fire resistance aura") {}
	};

	class CastSealOfRighteousnessAction : public CastBuffSpellAction {
	public:
		CastSealOfRighteousnessAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "seal of righteousness") {}
	};

	class CastSealOfJusticeAction : public CastBuffSpellAction {
	public:
		CastSealOfJusticeAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "seal of justice") {}
	};
    

	class CastSealOfLightAction : public CastBuffSpellAction {
	public:
		CastSealOfLightAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "seal of light") {}
	};

	class CastSealOfWisdomAction : public CastBuffSpellAction {
	public:
		CastSealOfWisdomAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "seal of wisdom") {}
	};

	class CastSealOfCommandAction : public CastBuffSpellAction {
	public:
		CastSealOfCommandAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "seal of command") {}
	};

    
	class CastBlessingOfMightAction : public CastBuffSpellAction {
	public:
		CastBlessingOfMightAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "blessing of might") {}
	};

	class CastBlessingOfMightOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfMightOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "blessing of might") {}
        virtual const char* getName() { return "blessing of might on party";}
	};

	class CastBlessingOfWisdomAction : public CastBuffSpellAction {
	public:
		CastBlessingOfWisdomAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "blessing of wisdom") {}
	};

	class CastBlessingOfWisdomOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfWisdomOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "blessing of wisdom") {}
        virtual const char* getName() { return "blessing of wisdom on party";}
	};

	class CastBlessingOfKingsAction : public CastBuffSpellAction {
	public:
		CastBlessingOfKingsAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "blessing of kings") {}
	};

	class CastBlessingOfKingsOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfKingsOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "blessing of kings") {}
        virtual const char* getName() { return "blessing of kings on party";}
	};

	class CastBlessingOfSanctuaryAction : public CastBuffSpellAction {
	public:
		CastBlessingOfSanctuaryAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "blessing of sanctuary") {}
	};

	class CastBlessingOfSanctuaryOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfSanctuaryOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "blessing of sanctuary") {}
        virtual const char* getName() { return "blessing of sanctuary on party";}
	};

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

	class CastDivineProtectionAction : public CastBuffSpellAction {
	public:
		CastDivineProtectionAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "divine protection") {}
	};

    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "divine protection") {}

        virtual const char* getName() { return "divine protection on party"; }
    };

	class CastDivineShieldAction: public CastBuffSpellAction {
	public:
		CastDivineShieldAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "divine shield") {}
	};

    BEGIN_SPELL_ACTION(CastConsecrationAction, "consecration")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyWrathAction, "holy wrath")
    END_SPELL_ACTION()

    class CastHammerOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastHammerOfJusticeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

	class CastHammerOfWrathAction : public CastMeleeSpellAction {
	public:
		CastHammerOfWrathAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "hammer of wrath") {}
	};

	class CastHammerOfTheRighteousAction : public CastMeleeSpellAction {
	public:
		CastHammerOfTheRighteousAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "hammer of the righteous") {}
	};

	class CastPurifyAction : public CastCureSpellAction {
	public:
		CastPurifyAction(PlayerbotAIFacade* const ai) : CastCureSpellAction(ai, "purify") {}
	};

    class CastPurifyOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}

        virtual const char* getName() { return "purify on party"; }
    };

	class CastHandOfReckoningAction : public CastDebuffSpellAction {
	public:
		CastHandOfReckoningAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "hand of reckoning") {}
	};

	class CastCleanseAction : public CastCureSpellAction {
	public:
		CastCleanseAction(PlayerbotAIFacade* const ai) : CastCureSpellAction(ai, "cleanse") {}
	};

    class CastCleanseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}

        virtual const char* getName() { return "cleanse on party"; }
    };

    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastExorcismAction, "exorcism")
	END_SPELL_ACTION()

	class CastHolyShieldAction : public CastBuffSpellAction {
	public:
		CastHolyShieldAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "holy shield") {}
	};
	
	class CastRedemptionAction : public ResurrectPartyMemberAction
	{
	public:
		CastRedemptionAction(PlayerbotAIFacade* const ai) : ResurrectPartyMemberAction(ai, "redemption") {}
	};
}