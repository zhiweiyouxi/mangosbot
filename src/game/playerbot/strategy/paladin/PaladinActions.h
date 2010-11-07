#pragma once
#include "../GenericActions.h"

namespace ai
{
    class CastJudgementOfLightAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfLightAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "judgement of light") {}
    };

    class CastJudgementOfWisdomAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfWisdomAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "judgement of wisdom") {}
    };

    class CastJudgementOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastJudgementOfJusticeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "judgement of justice") {}
    };

	class CastRighteousFuryAction : public CastBuffSpellAction {
	public:
		CastRighteousFuryAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "righteous fury") {}
	};

	class CastDevotionAuraAction : public CastBuffSpellAction {
	public:
		CastDevotionAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "devotion aura") {}
	};

	class CastRetributionAuraAction : public CastBuffSpellAction {
	public:
		CastRetributionAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "retribution aura") {}
	};

	class CastConcentrationAuraAction : public CastBuffSpellAction {
	public:
		CastConcentrationAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "concentration aura") {}
	};

	class CastShadowResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastShadowResistanceAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "shadow resistance aura") {}
	};

	class CastFrostResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFrostResistanceAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "frost resistance aura") {}
	};

	class CastFireResistanceAuraAction : public CastBuffSpellAction {
	public:
		CastFireResistanceAuraAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "fire resistance aura") {}
	};

	class CastSealOfRighteousnessAction : public CastBuffSpellAction {
	public:
		CastSealOfRighteousnessAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "seal of righteousness") {}
	};

	class CastSealOfJusticeAction : public CastBuffSpellAction {
	public:
		CastSealOfJusticeAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "seal of justice") {}
	};
    

	class CastSealOfLightAction : public CastBuffSpellAction {
	public:
		CastSealOfLightAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "seal of light") {}
	};

	class CastSealOfWisdomAction : public CastBuffSpellAction {
	public:
		CastSealOfWisdomAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "seal of wisdom") {}
	};

	class CastSealOfCommandAction : public CastBuffSpellAction {
	public:
		CastSealOfCommandAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "seal of command") {}
	};

    
	class CastBlessingOfMightAction : public CastBuffSpellAction {
	public:
		CastBlessingOfMightAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "blessing of might") {}
	};

	class CastBlessingOfMightOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfMightOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "blessing of might") {}
        virtual const char* getName() { return "blessing of might on party";}
	};

	class CastBlessingOfWisdomAction : public CastBuffSpellAction {
	public:
		CastBlessingOfWisdomAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "blessing of wisdom") {}
	};

	class CastBlessingOfWisdomOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfWisdomOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "blessing of wisdom") {}
        virtual const char* getName() { return "blessing of wisdom on party";}
	};

	class CastBlessingOfKingsAction : public CastBuffSpellAction {
	public:
		CastBlessingOfKingsAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "blessing of kings") {}
	};

	class CastBlessingOfKingsOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfKingsOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "blessing of kings") {}
        virtual const char* getName() { return "blessing of kings on party";}
	};

	class CastBlessingOfSanctuaryAction : public CastBuffSpellAction {
	public:
		CastBlessingOfSanctuaryAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "blessing of sanctuary") {}
	};

	class CastBlessingOfSanctuaryOnPartyAction : public BuffOnPartyAction {
	public:
		CastBlessingOfSanctuaryOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "blessing of sanctuary") {}
        virtual const char* getName() { return "blessing of sanctuary on party";}
	};

    class CastHolyLightAction : public CastHealingSpellAction {
    public:
        CastHolyLightAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "holy light") {}
    };

    class CastHolyLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHolyLightOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "holy light") {}

        virtual const char* getName() { return "holy light on party"; }
    };

    class CastFlashOfLightAction : public CastHealingSpellAction {
    public:
        CastFlashOfLightAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "flash of light") {}
    };

    class CastFlashOfLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashOfLightOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "flash of light") {}

        virtual const char* getName() { return "flash of light on party"; }
    };

    class CastLayOnHandsAction : public CastHealingSpellAction {
    public:
        CastLayOnHandsAction(AiManagerRegistry* const ai) : CastHealingSpellAction(ai, "lay on hands") {}
    };

    class CastLayOnHandsOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLayOnHandsOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "lay on hands") {}

        virtual const char* getName() { return "lay on hands on party"; }
    };

	class CastDivineProtectionAction : public CastBuffSpellAction {
	public:
		CastDivineProtectionAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "divine protection") {}
	};

    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(AiManagerRegistry* const ai) : HealPartyMemberAction(ai, "divine protection") {}

        virtual const char* getName() { return "divine protection on party"; }
    };

	class CastDivineShieldAction: public CastBuffSpellAction {
	public:
		CastDivineShieldAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "divine shield") {}
	};

    BEGIN_SPELL_ACTION(CastConsecrationAction, "consecration")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyWrathAction, "holy wrath")
    END_SPELL_ACTION()

    class CastHammerOfJusticeAction : public CastMeleeSpellAction {
    public:
        CastHammerOfJusticeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

	class CastHammerOfWrathAction : public CastMeleeSpellAction {
	public:
		CastHammerOfWrathAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "hammer of wrath") {}
	};

	class CastHammerOfTheRighteousAction : public CastMeleeSpellAction {
	public:
		CastHammerOfTheRighteousAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "hammer of the righteous") {}
	};

	class CastPurifyAction : public CastCureSpellAction {
	public:
		CastPurifyAction(AiManagerRegistry* const ai) : CastCureSpellAction(ai, "purify") {}
	};

    class CastPurifyOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyOnPartyAction(AiManagerRegistry* const ai) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}

        virtual const char* getName() { return "purify on party"; }
    };

	class CastHandOfReckoningAction : public CastDebuffSpellAction {
	public:
		CastHandOfReckoningAction(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "hand of reckoning") {}
	};

	class CastCleanseAction : public CastCureSpellAction {
	public:
		CastCleanseAction(AiManagerRegistry* const ai) : CastCureSpellAction(ai, "cleanse") {}
	};

    class CastCleanseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleanseOnPartyAction(AiManagerRegistry* const ai) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}

        virtual const char* getName() { return "cleanse on party"; }
    };

    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastExorcismAction, "exorcism")
	END_SPELL_ACTION()

	class CastHolyShieldAction : public CastBuffSpellAction {
	public:
		CastHolyShieldAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "holy shield") {}
	};
	
	class CastRedemptionAction : public ResurrectPartyMemberAction
	{
	public:
		CastRedemptionAction(AiManagerRegistry* const ai) : ResurrectPartyMemberAction(ai, "redemption") {}
	};
}