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
        virtual BOOL Execute() {
            ai->Flee(); return TRUE;
        }
    };

    class MeleeAction : public Action {
    public:
        MeleeAction(PlayerbotAIFacade* const ai) : Action(ai, "melee") {}
        virtual BOOL Execute() {
            ai->Melee(); return TRUE;
        }
    };

    class UseHealingPotion : public Action {
    public:
        UseHealingPotion(PlayerbotAIFacade* const ai) : Action(ai, "healing potion") {}
        virtual BOOL Execute() {
            ai->UseHealingPotion(); return TRUE;
        }
        virtual BOOL isPossible() {
            return ai->HasHealingPotion();
        }
    };

    class UseManaPotion : public Action {
    public:
        UseManaPotion(PlayerbotAIFacade* const ai) : Action(ai, "mana potion") {}
        virtual BOOL Execute() {
            ai->UseManaPotion(); return TRUE;
        }
        virtual BOOL isPossible() {
            return ai->HasManaPotion();
        }
    };

    class UsePanicPotion : public Action {
    public:
        UsePanicPotion(PlayerbotAIFacade* const ai) : Action(ai, "panic potion") {}
        virtual BOOL Execute() {
            ai->UsePanicPotion(); return TRUE;
        }
        virtual BOOL isPossible() {
            return ai->HasPanicPotion();
        }
    };

    class LootAction : public Action {
    public:
        LootAction(PlayerbotAIFacade* const ai) : Action(ai, "loot") {}
        virtual BOOL Execute() {
            ai->Loot(); return TRUE;
        }
    };

    class EmoteAction : public Action
    {
    public:
        EmoteAction(PlayerbotAIFacade* const ai, uint32 type) : Action(ai, "emote") {
            this->type = type;
        }

        BOOL Execute() {
            ai->Emote(type ? type : rand() % 450);
            return TRUE;
        }

    protected:
        uint32 type;
    };
}