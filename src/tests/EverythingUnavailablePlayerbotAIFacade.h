#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

namespace ai
{
    class EverythingUnavailablePlayerbotAIFacade : public MockPlayerbotAIFacade
    {
    public:
        EverythingUnavailablePlayerbotAIFacade() : MockPlayerbotAIFacade() {}

        virtual BOOL canCastSpell(const char* spell) { return FALSE; }
    };

}