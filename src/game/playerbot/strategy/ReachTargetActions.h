#pragma once

#include "Action.h"

namespace ai
{
    class ReachTargetAction : public Action {
    public:
        ReachTargetAction(AiManagerRegistry* const ai, const char* name, float distance) : Action(ai, name) 
		{
            this->distance = distance;
        }
        virtual void Execute() 
		{
			ai->GetMoveManager()->MoveTo(ai->GetTargetManager()->GetCurrentTarget(), distance);
        }
        virtual bool isUseful() 
		{
            return ai->GetMoveManager()->GetDistanceTo(ai->GetTargetManager()->GetCurrentTarget()) > distance;
        }

    protected:
        float distance;
    };

    class CastReachTargetSpellAction : public CastSpellAction {
    public:
        CastReachTargetSpellAction(AiManagerRegistry* const ai, const char* spell, float distance) : CastSpellAction(ai, spell) 
		{
            this->distance = distance;
        }
		virtual bool isUseful() 
		{
			return ai->GetMoveManager()->GetDistanceTo(ai->GetTargetManager()->GetCurrentTarget()) > distance;
		}

    protected:
        float distance;
    };

    class ReachMeleeAction : public ReachTargetAction 
	{
    public:
        ReachMeleeAction(AiManagerRegistry* const ai) : ReachTargetAction(ai, "reach melee", 1.5f) {}
    };

    class ReachSpellAction : public ReachTargetAction 
	{
    public:
        ReachSpellAction(AiManagerRegistry* const ai, float distance = SPELL_DISTANCE) : ReachTargetAction(ai, "reach spell", distance) {}
    };
}