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
        CastSpellAction(PlayerbotAIFacade* const ai, const char* spell) : Action(ai)
        {
            this->spell = spell;
        }

        void Execute() { ai->CastSpell(spell); }
        virtual BOOL isAvailable() { return ai->canCastSpell(spell) && ai->GetDistanceToEnemy() < BOT_REACT_DISTANCE; }
        virtual const char* getName() { return spell; }

    protected:
        const char* spell;
    };


    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual BOOL isAvailable();
    };
    //---------------------------------------------------------------------------------------------------------------------

    class CastRangedSpellAction : public CastSpellAction
    {
    public:
        CastRangedSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

        PREREQUISITE_ACTIONS("reach spell");
    };
    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual BOOL isAvailable();
        PREREQUISITE_ACTIONS("reach spell");
    };
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(FleeAction, "flee")
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(MeleeAction, "melee")
        virtual BOOL isUseful();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(ReachSpellAction, "reach spell")
        virtual BOOL isUseful();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "lifeblood")
        ALTERNATIVE_ACTIONS("regrowth")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UseHealingPotion, "healing potion")
        ALTERNATIVE_ACTIONS("mana potion")
        virtual BOOL isAvailable();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UseManaPotion, "mana potion")
        ALTERNATIVE_ACTIONS("flee")
        virtual BOOL isAvailable();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UsePanicPotion, "panic potion")
        ALTERNATIVE_ACTIONS("healing potion")
        virtual BOOL isAvailable();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------
    
    class HealPartyMemberAction : public CastSpellAction
    {
    public:
        HealPartyMemberAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

        PREREQUISITE_ACTIONS("reach spell");
        virtual void Execute();
        virtual BOOL isUseful();
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastSpellAction
    {
    public:
        BuffOnPartyAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
    public: 
        virtual void Execute();
        virtual BOOL isUseful();
    };

    //---------------------------------------------------------------------------------------------------------------------
    
    BEGIN_ACTION(AttackLeastThreatAction, "attack least threat")
    END_ACTION()
  
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(AttackBiggerThreatAction, "attack bigger threat")
    END_ACTION()
}