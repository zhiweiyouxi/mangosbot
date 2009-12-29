#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class MageEnemyTooCloseTrigger : public EnemyTooCloseTrigger
    {
    public:
        MageEnemyTooCloseTrigger(PlayerbotAIFacade* const ai) : EnemyTooCloseTrigger(ai) {}
        virtual NextAction** getNextActions();
    };
}