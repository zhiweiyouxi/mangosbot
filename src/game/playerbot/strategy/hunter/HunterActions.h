#pragma once

#include "../GenericActions.h"

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastHuntersMarkAction, "hunter's mark")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastAutoShotAction, "auto shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastExplosiveShotAction, "explosive shot")
        virtual bool isUseful();
    END_SPELL_ACTION()
        

    BEGIN_RANGED_SPELL_ACTION(CastAimedShotAction, "aimed shot")
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastConcussiveShotAction, "concussive shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSerpentStingAction, "serpent sting")
    virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastWyvernStingAction, "wyvern sting")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastViperStingAction, "viper sting")
    virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    END_SPELL_ACTION()

	class CastAspectOfTheHawkAction : public CastBuffSpellAction {
	public:
		CastAspectOfTheHawkAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "aspect of the hawk") {}
	};

	class CastAspectOfTheCheetahAction : public CastBuffSpellAction {
	public:
		CastAspectOfTheCheetahAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "aspect of the cheetah") {}
		virtual bool isUseful();
	};

	class CastAspectOfThePackAction : public CastBuffSpellAction {
	public:
		CastAspectOfThePackAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "aspect of the pack") {}
	};

	class CastAspectOfTheViperAction : public CastBuffSpellAction {
	public:
		CastAspectOfTheViperAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "aspect of the viper") {}
		virtual bool isUseful();
	};

	class CastCallPetAction : public CastBuffSpellAction {
	public:
		CastCallPetAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "call pet") {}
	};

	class CastMendPetAction : public CastAuraSpellAction {
	public:
		CastMendPetAction(AiManagerRegistry* const ai) : CastAuraSpellAction(ai, "mend pet") {}
		virtual Unit* GetTarget();
	};

	class CastRevivePetAction : public CastBuffSpellAction {
	public:
		CastRevivePetAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "revive pet") {}
	};

	class CastRapidFireAction : public CastBuffSpellAction {
	public:
		CastRapidFireAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "rapid fire") {}
	};

	class CastReadynessAction : public CastBuffSpellAction {
	public:
		CastReadynessAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "readyness") {}
	};

	class CastBlackArrow : public CastDebuffSpellAction {
	public:
		CastBlackArrow(AiManagerRegistry* const ai) : CastDebuffSpellAction(ai, "black arrow") {}
	};
   
}