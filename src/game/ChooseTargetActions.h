#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"

namespace ai
{
    class AttackLeastThreatAction : public Action {
    public:
        AttackLeastThreatAction(PlayerbotAIFacade* const ai) : Action(ai, "attack least threat") {}
        virtual void Execute() {
            ai->AttackLeastThreat();
        }
    };   
    
    class AttackBiggerThreatAction : public Action {
    public:
        AttackBiggerThreatAction(PlayerbotAIFacade* const ai) : Action(ai, "attack bigger threat") {}
        virtual void Execute() {
            ai->AttackBiggerThreat();
        }
    };   
  
   
}