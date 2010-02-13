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

        BOOL Execute() { return ai->CastSpell(spell); }
        virtual BOOL isPossible() { return ai->canCastSpell(spell) && ai->GetDistanceToEnemy() < BOT_REACT_DISTANCE; }
        virtual const char* getName() { return spell; }

    protected:
        const char* spell;
    };


    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual BOOL isPossible();
        virtual NextAction** getPrerequisites();
    };
    //---------------------------------------------------------------------------------------------------------------------

    class CastRangedSpellAction : public CastSpellAction
    {
    public:
        CastRangedSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites();

    };
    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
        virtual BOOL isPossible();
    };
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(FleeAction, "flee")
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(MeleeAction, "melee")
    END_ACTION()

    BEGIN_ACTION(ReachMeleeAction, "reach melee")
        virtual BOOL isUseful();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(ReachSpellAction, "reach spell")
        virtual BOOL isUseful();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "lifeblood")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastGiftOfTheNaaruAction, "gift of the naaru")
        virtual BOOL isUseful();
    END_SPELL_ACTION()
        

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UseHealingPotion, "healing potion")
        virtual BOOL isPossible();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UseManaPotion, "mana potion")
        virtual BOOL isPossible();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(UsePanicPotion, "panic potion")
        virtual BOOL isPossible();
    END_ACTION()

    //---------------------------------------------------------------------------------------------------------------------
    
    class HealPartyMemberAction : public CastSpellAction
    {
    public:
        HealPartyMemberAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

        virtual BOOL Execute();
        virtual BOOL isUseful();
    };

    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastSpellAction
    {
    public:
        BuffOnPartyAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
    public: 
        virtual BOOL Execute();
        virtual BOOL isUseful();
    };

    //---------------------------------------------------------------------------------------------------------------------
    
    BEGIN_ACTION(AttackLeastThreatAction, "attack least threat")
    END_ACTION()
  
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(AttackBiggerThreatAction, "attack bigger threat")
    END_ACTION()
    //---------------------------------------------------------------------------------------------------------------------

    BEGIN_ACTION(LootAction, "loot")
    END_ACTION()

    class EmoteAction : public Action
    {
    public:
        EmoteAction(PlayerbotAIFacade* const ai, uint32 name) : Action(ai)
        {
            this->name = name;
        }

        BOOL Execute();
        virtual const char* getName() { return "emote"; }

    protected:
        uint32 name;
    };

    BEGIN_RANGED_SPELL_ACTION(CastShootAction, "shoot")
    END_SPELL_ACTION()
}