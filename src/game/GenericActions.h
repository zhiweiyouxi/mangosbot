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

    class FollowAction : public Action {
    public:
        FollowAction(PlayerbotAIFacade* const ai) : Action(ai, "follow") {}
        virtual void Execute() {
            ai->FollowMaster(); 
        }
    };

    class StayAction : public Action {
    public:
        StayAction(PlayerbotAIFacade* const ai) : Action(ai, "stay") {}
        virtual void Execute() {
            ai->Stay(); 
        }
    };

    class GoAwayAction : public Action {
    public:
        GoAwayAction(PlayerbotAIFacade* const ai) : Action(ai, "goaway") {}
        virtual void Execute() {
            ai->GoAway(); 
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
        virtual bool isPossible() {
            return ai->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action {
    public:
        UseManaPotion(PlayerbotAIFacade* const ai) : Action(ai, "mana potion") {}
        virtual void Execute() {
            ai->UseManaPotion(); 
        }
        virtual bool isPossible() {
            return ai->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action {
    public:
        UsePanicPotion(PlayerbotAIFacade* const ai) : Action(ai, "panic potion") {}
        virtual void Execute() {
            ai->UsePanicPotion(); 
        }
        virtual bool isPossible() {
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