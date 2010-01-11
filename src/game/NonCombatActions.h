#pragma once

#include "Action.h"
#include "PlayerbotAIFacade.h"

namespace ai
{
    BEGIN_ACTION(FollowAction, "follow")
        virtual BOOL isUseful();
    END_ACTION()

    BEGIN_ACTION(StayAction, "stay")
    END_ACTION()

    BEGIN_ACTION(DrinkAction, "drink")
        virtual BOOL isUseful();
    END_ACTION()

    BEGIN_ACTION(EatAction, "eat")
        virtual BOOL isUseful();
    END_ACTION()

    BEGIN_ACTION(GoAwayAction, "goaway")
        virtual BOOL isUseful();
    END_ACTION()
}