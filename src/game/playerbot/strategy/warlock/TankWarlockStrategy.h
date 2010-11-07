#pragma once

#include "GenericWarlockStrategy.h"

namespace ai
{
    class TankWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        TankWarlockStrategy(AiManagerRegistry* const ai) : GenericWarlockStrategy(ai) {}
        virtual const char* getName() { return "tank"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}