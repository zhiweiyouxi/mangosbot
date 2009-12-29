#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class MageEnemyTooCloseTrigger : public EnemyTooCloseTrigger
    {
    public:
        MageEnemyTooCloseTrigger(PlayerbotAIFacade* const ai) : EnemyTooCloseTrigger(ai) {}
        virtual NextAction* getNextAction() { return new NextAction("frostnova", 10.0f); }
    };
}