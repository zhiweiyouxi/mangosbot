#pragma once

#include "Action.h"

namespace ai
{
    class DrinkAction : public Action {
    public:
        DrinkAction(AiManagerRegistry* const ai) : Action(ai, "drink") {}
        virtual void Execute() {
            ai->GetInventoryManager()->UseDrink();
        }
        virtual bool isUseful() {
            return ai->GetStatsManager()->GetManaPercent(ai->GetTargetManager()->GetSelf()) < EAT_DRINK_PERCENT && ai->GetInventoryManager()->HasDrink();
        }
    };

    class EatAction : public Action {
    public:
        EatAction(AiManagerRegistry* const ai) : Action(ai, "eat") {}
        virtual void Execute() {
            ai->GetInventoryManager()->UseFood();
        }
        virtual bool isUseful() {
            return ai->GetStatsManager()->GetHealthPercent(ai->GetTargetManager()->GetSelf()) < EAT_DRINK_PERCENT && 
				ai->GetInventoryManager()->HasFood();
        }
    };

}