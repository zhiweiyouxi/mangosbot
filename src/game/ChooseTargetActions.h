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

    class AttackLeastThreatAction : public AttackAction {
    public:
        AttackLeastThreatAction(AiManagerRegistry* const ai) : AttackAction(ai, "attack least threat") {}
        virtual Unit* GetTarget() 
        {
            return ai->GetTargetManager()->FindLeastThreat();
        }
    };   
    
    class AttackBiggerThreatAction : public AttackAction {
    public:
        AttackBiggerThreatAction(AiManagerRegistry* const ai) : AttackAction(ai, "attack bigger threat") {}
        virtual Unit* GetTarget() 
        {
            return ai->GetTargetManager()->FindBiggerThreat();
        }
    };   
  
   
}