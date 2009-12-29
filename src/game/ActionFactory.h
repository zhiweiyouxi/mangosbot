#pragma once

#include "PlayerbotAIFacadeAware.h"
#include "Action.h"

namespace ai
{
    class ActionFactory : public PlayerbotAIFacadeAware
    {
    public:
        ActionFactory(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~ActionFactory() {}

    public:
        virtual Action* createAction(const char* name);
    };
}