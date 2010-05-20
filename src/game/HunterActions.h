#pragma once

#include "GenericActions.h"

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
		CastAspectOfTheHawkAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "aspect of the hawk") {}
	};

    BEGIN_SPELL_ACTION(CastAspectOfTheCheetahAction, "aspect of the cheetah")
        virtual bool isUseful();
    END_SPELL_ACTION()

	class CastAspectOfThePackAction : public CastBuffSpellAction {
	public:
		CastAspectOfThePackAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "aspect of the pack") {}
	};

	class CastAspectOfTheViperAction : public CastBuffSpellAction {
	public:
		CastAspectOfTheViperAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "aspect of the viper") {}
		virtual bool isUseful();
	};

    BEGIN_SPELL_ACTION(CastCallPetAction, "call pet")
    END_SPELL_ACTION()

	class CastMendPetAction : public CastAuraSpellAction {
	public:
		CastMendPetAction(PlayerbotAIFacade* const ai) : CastAuraSpellAction(ai, "mend pet") {}
		virtual Unit* GetTarget();
	};

    BEGIN_SPELL_ACTION(CastRevivePetAction, "revive pet")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRapidFireAction, "rapid fire")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastReadynessAction, "readyness")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastBlackArrow, "black arrow")
    END_SPELL_ACTION()
   
}