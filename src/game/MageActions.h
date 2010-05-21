#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_SPELL_ACTION(CastFrostNovaAction, "frost nova")
    END_SPELL_ACTION()

	class CastFrostboltAction : public CastSpellAction
	{
	public:
		CastFrostboltAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "frostbolt") {}
	};


	class CastArcaneIntellectAction : public CastBuffSpellAction {
	public:
		CastArcaneIntellectAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "arcane intellect") {}
	};

	class CastArcaneIntellectOnPartyAction : public BuffOnPartyAction {
	public:
		CastArcaneIntellectOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "arcane intellect") {}
	};

	class CastRemoveCurseAction : public CastCureSpellAction {
	public:
		CastRemoveCurseAction(PlayerbotAIFacade* const ai) : CastCureSpellAction(ai, "remove curse") {}
	};

	class CastIcyVeinsAction : public CastBuffSpellAction {
	public:
		CastIcyVeinsAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "icy veins") {}
	};

    BEGIN_SPELL_ACTION(CastCounterspellAction, "counterspell")
    END_SPELL_ACTION()

    class CastRemoveCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveCurseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "remove curse", DISPEL_CURSE) {}
    };

	class CastConjureFoodAction : public CastBuffSpellAction {
	public:
		CastConjureFoodAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "conjure food") {}
	};

	class CastConjureWaterAction : public CastBuffSpellAction {
	public:
		CastConjureWaterAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "conjure water") {}
	};

	class CastIceBlockAction : public CastBuffSpellAction {
	public:
		CastIceBlockAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "ice block") {}
	};
}