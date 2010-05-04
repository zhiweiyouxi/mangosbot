#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"

namespace ai
{
    class DrinkAction : public Action {
    public:
        DrinkAction(PlayerbotAIFacade* const ai) : Action(ai, "drink") {}
        virtual void Execute() {
            ai->UseDrink();
        }
        virtual bool isUseful() {
            return ai->GetManaPercent() < EAT_DRINK_PERCENT && !ai->HasAura("drink") && ai->HasDrink();
        }
    };

    class EatAction : public Action {
    public:
        EatAction(PlayerbotAIFacade* const ai) : Action(ai, "eat") {}
        virtual void Execute() {
            ai->UseFood();
        }
        virtual bool isUseful() {
            return ai->GetHealthPercent() < EAT_DRINK_PERCENT && !ai->HasAura("eat") && ai->HasFood();
        }
    };

}