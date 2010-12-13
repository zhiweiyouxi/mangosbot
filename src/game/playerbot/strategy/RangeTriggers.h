#pragma once
#include "Trigger.h"

namespace ai
{
    class EnemyTooCloseTrigger : public Trigger {
    public:
        EnemyTooCloseTrigger(AiManagerRegistry* const ai) : Trigger(ai, "enemy too close") {}
        virtual bool IsActive() 
		{
			Unit* target = targetManager->GetCurrentTarget();
            float distance = moveManager->GetDistanceTo(target);
            return target && distance <= ATTACK_DISTANCE;
        }
    };

    class EnemyOutOfRangeTrigger : public Trigger {
    public:
        EnemyOutOfRangeTrigger(AiManagerRegistry* const ai, const char* name, float distance) : Trigger(ai, name) 
		{
            this->distance = distance;
        }
        virtual bool IsActive() 
		{
			Unit* target = targetManager->GetCurrentTarget();
			return target && moveManager->GetDistanceTo(target) > distance;
        }

    protected:
        float distance;
    };

    class EnemyOutOfMeleeTrigger : public EnemyOutOfRangeTrigger 
	{
    public:
        EnemyOutOfMeleeTrigger(AiManagerRegistry* const ai) : EnemyOutOfRangeTrigger(ai, "enemy out of melee range", ATTACK_DISTANCE) {}
    };

    class EnemyOutOfSpellRangeTrigger : public EnemyOutOfRangeTrigger 
	{
    public:
        EnemyOutOfSpellRangeTrigger(AiManagerRegistry* const ai) : EnemyOutOfRangeTrigger(ai, "enemy out of spell range", SPELL_DISTANCE) {}
    };
}