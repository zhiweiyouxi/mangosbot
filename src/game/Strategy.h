#pragma once
#include "Action.h"
#include "Multiplier.h"
#include "Trigger.h"

namespace ai
{
    class Strategy : public PlayerbotAIFacadeAware
    {
    public:
        Strategy(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~Strategy() {}

    public:
        virtual NextAction** getNextActions() { return NULL; }
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers) {}
        virtual const char* getName() { return NULL; }
    };
}
