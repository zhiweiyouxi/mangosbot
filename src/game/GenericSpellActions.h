#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"

#define BEGIN_SPELL_ACTION(clazz, name) \
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastSpellAction(ai, name) {} \


#define END_SPELL_ACTION() \
    };

#define BEGIN_DEBUFF_ACTION(clazz, name) \
class clazz : public CastDebuffSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, name) {} \

#define BEGIN_RANGED_SPELL_ACTION(clazz, name) \
class clazz : public CastRangedSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, name) {} \

#define BEGIN_MELEE_SPELL_ACTION(clazz, name) \
class clazz : public CastMeleeSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, name) {} \


#define END_RANGED_SPELL_ACTION() \
    };


#define BEGIN_BUFF_ON_PARTY_ACTION(clazz, name) \
class clazz : public BuffOnPartyAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, name) {} 

namespace ai
{
    class CastSpellAction : public Action
    {
    public:
        CastSpellAction(PlayerbotAIFacade* const ai, const char* spell) : Action(ai, spell)
        {
            this->spell = spell;
        }

        bool ExecuteResult() { return ai->CastSpell(spell); }
        virtual bool isPossible() { return ai->canCastSpell(spell) && ai->GetDistanceToEnemy() < BOT_REACT_DISTANCE; }

    protected:
        const char* spell;
    };

	//---------------------------------------------------------------------------------------------------------------------
	class CastAuraSpellAction : public CastSpellAction
	{
	public:
		CastAuraSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

		virtual bool isPossible() 
		{
			return CastSpellAction::isPossible() && !ai->HasAura(spell);
		}
		virtual bool isUseful() 
		{
			return CastSpellAction::isUseful() && !ai->HasAura(spell);
		}
	};

    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), NULL), CastSpellAction::getPrerequisites());
        }
    };
    //---------------------------------------------------------------------------------------------------------------------

    class CastRangedSpellAction : public CastSpellAction
    {
    public:
        CastRangedSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("reach spell"), NULL), CastSpellAction::getPrerequisites());
        }

    };
    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual bool isPossible();
    };
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "lifeblood")
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastGiftOfTheNaaruAction, "gift of the naaru")
        virtual bool isUseful();
    END_SPELL_ACTION()
        
    //---------------------------------------------------------------------------------------------------------------------
    
    class CastHealingSpellAction : public CastSpellAction
    {
    public:
        CastHealingSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual bool isUseful() {
            return CastSpellAction::isUseful() && ai->GetHealthPercent() < 70;
        }
    };
    class HealPartyMemberAction : public CastSpellAction
    {
    public:
        HealPartyMemberAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

        virtual bool isUseful();
        virtual bool ExecuteResult();
    };

    //---------------------------------------------------------------------------------------------------------------------

    class CurePartyMemberAction : public CastSpellAction
    {
    public:
        CurePartyMemberAction(PlayerbotAIFacade* const ai, const char* spell, uint32 dispelType) : CastSpellAction(ai, spell) 
        {
            this->dispelType = dispelType;
        }

        virtual bool ExecuteResult();

    protected:
        uint32 dispelType;
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastSpellAction
    {
    public:
        BuffOnPartyAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
    public: 
        virtual bool ExecuteResult();
        virtual bool isUseful();
    };

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_RANGED_SPELL_ACTION(CastShootAction, "shoot")
    END_SPELL_ACTION()
}