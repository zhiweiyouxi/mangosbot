#pragma once

#include "Action.h"
#include "AiManagerRegistry.h"

namespace ai
{
    class AttackAction : public Action {
    public:
        AttackAction(AiManagerRegistry* const ai, const char* name) : Action(ai, name) {}
        
        virtual Unit* GetTarget() = NULL;

        virtual void Execute() {
            Unit* target = GetTarget();
            if (target)
                ai->GetMoveManager()->Attack(target);
        }
    };   

    class DpsAssistAction : public AttackAction {
    public:
        DpsAssistAction(AiManagerRegistry* const ai) : AttackAction(ai, "dps assist") {}
        virtual Unit* GetTarget() 
        {
            return ai->GetTargetManager()->FindTargetForDps();
        }
    };   
    
    class TankAssistAction : public AttackAction {
    public:
        TankAssistAction(AiManagerRegistry* const ai) : AttackAction(ai, "tank assist") {}
        virtual Unit* GetTarget() 
        {
            return ai->GetTargetManager()->FindTargetForTank();
        }
    };   
  
   
}