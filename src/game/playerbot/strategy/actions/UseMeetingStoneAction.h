#pragma once

#include "../Action.h"

namespace ai
{
    class UseMeetingStoneAction : public Action {
    public:
        UseMeetingStoneAction(PlayerbotAI* ai) : Action(ai, "use meeting stone") {}

        virtual bool Execute(Event event);
    };

}
