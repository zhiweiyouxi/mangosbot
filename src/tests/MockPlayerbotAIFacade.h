#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

class MockPlayerbotAIFacade : public PlayerbotAIFacade
{
public:
    MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL) {}

    virtual float GetDistanceToEnemy() { return 0; }
    virtual void MoveToMaster() { buffer = buffer.append(">MoveToMaster"); }
    virtual void CastSpell(const char* spell) { buffer.append(">CastSpell:").append(spell); }

    std::string buffer;
};

