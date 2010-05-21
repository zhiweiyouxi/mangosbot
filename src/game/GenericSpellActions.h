#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"
#include "AiSpellManager.h"
#include "AiTargetManager.h"
#include "AiStatsManager.h"

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
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastSpellAction(ai, name) {} \

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
        CastSpellAction(PlayerbotAIFacade* const ai, const char* spell) : Action(ai, spell),
			range(SPELL_DISTANCE)
        {
            this->spell = spell;
			this->spellManager = ai->GetSpellManager();
			this->targetManager = ai->GetTargetManager();
			this->statsManager = ai->GetStatsManager();
        }

		virtual Unit* GetTarget();
        virtual bool ExecuteResult();
        virtual bool isPossible();
		virtual bool isUseful();

		virtual NextAction** getPrerequisites() 
		{
			if (range > SPELL_DISTANCE)
				return NULL;
			else if (range > ATTACK_DISTANCE)
				return NextAction::merge( NextAction::array(0, new NextAction("reach spell"), NULL), Action::getPrerequisites());
			else
				return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), NULL), Action::getPrerequisites());
		}

    protected:
        const char* spell;
		float range;
		AiSpellManager* spellManager;
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
    };

	//---------------------------------------------------------------------------------------------------------------------
	class CastAuraSpellAction : public CastSpellAction
	{
	public:
		CastAuraSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

		virtual bool isPossible();
		virtual bool isUseful();
	};

    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {
			range = ATTACK_DISTANCE;
		}
    };

    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastAuraSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastAuraSpellAction(ai, spell) {}
    };

	class CastBuffSpellAction : public CastAuraSpellAction
	{
	public:
		CastBuffSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastAuraSpellAction(ai, spell) 
		{
			range = BOT_REACT_DISTANCE;
		}
		virtual Unit* GetTarget();
	};

    //---------------------------------------------------------------------------------------------------------------------
    
    class CastHealingSpellAction : public CastAuraSpellAction
    {
    public:
        CastHealingSpellAction(PlayerbotAIFacade* const ai, const char* spell, uint8 estAmount = 15.0f) : CastAuraSpellAction(ai, spell) 
		{
            this->estAmount = estAmount;
			range = BOT_REACT_DISTANCE;
        }
		virtual Unit* GetTarget();
        virtual bool isUseful();

    protected:
        uint8 estAmount;
    };

	class CastCureSpellAction : public CastSpellAction
	{
	public:
		CastCureSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) 
		{
			range = BOT_REACT_DISTANCE;
		}

		virtual Unit* GetTarget();
	};

	class PartyMemberActionNameSupport {
	public:
		PartyMemberActionNameSupport(const char* spell) 
		{
			name = string(spell) + " on party";
		}

		virtual const char* getName() { return name.c_str(); }

	private:
		string name;
	};

    class HealPartyMemberAction : public CastHealingSpellAction, public PartyMemberActionNameSupport
    {
    public:
        HealPartyMemberAction(PlayerbotAIFacade* const ai, const char* spell, uint8 estAmount = 15.0f) : 
			CastHealingSpellAction(ai, spell, estAmount), PartyMemberActionNameSupport(spell) {}

		virtual Unit* GetTarget();
		virtual const char* getName() { return PartyMemberActionNameSupport::getName(); }
    };

	class ResurrectPartyMemberAction : public CastSpellAction
	{
	public:
		ResurrectPartyMemberAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

		virtual Unit* GetTarget();
	};
    //---------------------------------------------------------------------------------------------------------------------

    class CurePartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        CurePartyMemberAction(PlayerbotAIFacade* const ai, const char* spell, uint32 dispelType) : 
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        {
            this->dispelType = dispelType;
        }

		virtual Unit* GetTarget();
		virtual const char* getName() { return PartyMemberActionNameSupport::getName(); }

    protected:
        uint32 dispelType;
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        BuffOnPartyAction(PlayerbotAIFacade* const ai, const char* spell) : 
			CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell) {}
    public: 
		virtual Unit* GetTarget();
		virtual const char* getName() { return PartyMemberActionNameSupport::getName(); }
    };

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_RANGED_SPELL_ACTION(CastShootAction, "shoot")
    END_SPELL_ACTION()


	class CastLifeBloodAction : public CastHealingSpellAction
	{
	public:
		CastLifeBloodAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "lifeblood") {}
	};

	class CastGiftOfTheNaaruAction : public CastHealingSpellAction
	{
	public:
		CastGiftOfTheNaaruAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "gift of the naaru") {}
	};
}