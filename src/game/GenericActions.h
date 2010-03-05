#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"
#include "GenericSpellActions.h"

namespace ai
{
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
}