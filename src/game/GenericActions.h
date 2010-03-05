#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"

namespace ai
{
    class FleeAction : public Action {
    public:
        FleeAction(PlayerbotAIFacade* const ai) : Action(ai, "flee") {}
        virtual void Execute() {
            ai->Flee(); 
        }
    };

    class MeleeAction : public Action {
    public:
        MeleeAction(PlayerbotAIFacade* const ai) : Action(ai, "melee") {}
        virtual void Execute() {
            ai->Melee();
        }
    };

    class UseHealingPotion : public Action {
    public:
        UseHealingPotion(PlayerbotAIFacade* const ai) : Action(ai, "healing potion") {}
        virtual void Execute() {
            ai->UseHealingPotion(); 
        }
        virtual BOOL isPossible() {
            return ai->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action {
    public:
        UseManaPotion(PlayerbotAIFacade* const ai) : Action(ai, "mana potion") {}
        virtual void Execute() {
            ai->UseManaPotion(); 
        }
        virtual BOOL isPossible() {
            return ai->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action {
    public:
        UsePanicPotion(PlayerbotAIFacade* const ai) : Action(ai, "panic potion") {}
        virtual void Execute() {
            ai->UsePanicPotion(); 
        }
        virtual BOOL isPossible() {
            return ai->HasPanicPotion();
        }
    };

    class LootAction : public Action {
    public:
        LootAction(PlayerbotAIFacade* const ai) : Action(ai, "loot") {}
        virtual void Execute() {
            ai->Loot();
        }
    };

    class EmoteAction : public Action
    {
    public:
        EmoteAction(PlayerbotAIFacade* const ai, uint32 type) : Action(ai, "emote") {
            this->type = type;
        }

        virtual void Execute() {
            ai->Emote(type ? type : rand() % 450);
        }

    protected:
        uint32 type;
    };
}