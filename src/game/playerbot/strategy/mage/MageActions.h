#pragma once

#include "../GenericActions.h"

namespace ai
{
    class CastFireballAction : public CastSpellAction
    {
    public:
        CastFireballAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "fireball") {}
    };

    BEGIN_SPELL_ACTION(CastFrostNovaAction, "frost nova")
    END_SPELL_ACTION()

	class CastFrostboltAction : public CastSpellAction
	{
	public:
		CastFrostboltAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "frostbolt") {}
	};


	class CastArcaneIntellectAction : public CastBuffSpellAction 
    {
	public:
		CastArcaneIntellectAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "arcane intellect") {}
	};

	class CastArcaneIntellectOnPartyAction : public BuffOnPartyAction 
    {
	public:
		CastArcaneIntellectOnPartyAction(AiManagerRegistry* const ai) : BuffOnPartyAction(ai, "arcane intellect") {}
	};

	class CastRemoveCurseAction : public CastCureSpellAction 
    {
	public:
		CastRemoveCurseAction(AiManagerRegistry* const ai) : CastCureSpellAction(ai, "remove curse") {}
	};

	class CastIcyVeinsAction : public CastBuffSpellAction 
    {
	public:
		CastIcyVeinsAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "icy veins") {}
	};

    BEGIN_SPELL_ACTION(CastCounterspellAction, "counterspell")
    END_SPELL_ACTION()

    class CastRemoveCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveCurseOnPartyAction(AiManagerRegistry* const ai) : CurePartyMemberAction(ai, "remove curse", DISPEL_CURSE) {}
    };

	class CastConjureFoodAction : public CastBuffSpellAction 
    {
	public:
		CastConjureFoodAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "conjure food") {}
	};

	class CastConjureWaterAction : public CastBuffSpellAction 
    {
	public:
		CastConjureWaterAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "conjure water") {}
	};

	class CastIceBlockAction : public CastBuffSpellAction 
    {
	public:
		CastIceBlockAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "ice block") {}
	};

    class CastMageArmorAction : public CastBuffSpellAction 
    {
    public:
        CastMageArmorAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "mage armor") {}
    };

    class CastIceArmorAction : public CastBuffSpellAction 
    {
    public:
        CastIceArmorAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "ice armor") {}
    };

    class CastFrostArmorAction : public CastBuffSpellAction 
    {
    public:
        CastFrostArmorAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "frost armor") {}
    };
}