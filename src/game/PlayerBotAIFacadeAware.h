#pragma once

#include "PlayerbotAIFacade.h"

class PlayerbotAIFacadeAware 
{
public:
    PlayerbotAIFacadeAware(PlayerbotAIFacade* const ai) { this->ai = ai; }

protected:
    PlayerbotAIFacade* ai;
};