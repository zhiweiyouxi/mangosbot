#pragma once
#include "Trigger.h"

namespace ai
{

    class EnemyTooCloseTrigger : public Trigger
    {
    public:
        EnemyTooCloseTrigger(PlayerbotAIFacade* const ai) : Trigger(ai) {}

    public:
        virtual BOOL IsActive();
    };
}