#pragma once

#include "GenericWarlockStrategy.h"

namespace ai
{
    class DpsWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        DpsWarlockStrategy(AiManagerRegistry* const ai) : GenericWarlockStrategy(ai) {}
        virtual const char* getName() { return "dps"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}