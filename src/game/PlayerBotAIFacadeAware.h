#pragma once

#include "PlayerbotAIFacade.h"
namespace ai
{
    class PlayerbotAIFacadeAware 
    {
    public:
        PlayerbotAIFacadeAware(PlayerbotAIFacade* const ai) { this->ai = ai; }

    protected:
        PlayerbotAIFacade* ai;
    };
}