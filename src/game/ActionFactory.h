#pragma once

#include "PlayerbotAIFacadeAware.h"
#include "Action.h"
#include "Strategy.h"

#define CREATE_ACTION_RULE(actioname, clazz) \
    if (!strcmp(actioname, name)) \
        return new clazz(ai);


namespace ai
{
    class ActionFactory : public PlayerbotAIFacadeAware
    {
    public:
        ActionFactory(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~ActionFactory() {}

    public:
        virtual Action* createAction(const char* name);
        virtual Strategy* createStrategy(const char* name);
    };
}