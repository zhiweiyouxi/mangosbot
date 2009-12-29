#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

class MockPlayerbotAIFacade : public PlayerbotAIFacade
{
public:
    MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL) {}

    virtual float GetDistanceToEnemy() { return 0; }
    virtual void MoveToMaster() { buffer = buffer.append(">flee"); }
    virtual void CastSpell(const char* spell) { buffer.append(">spell:").append(spell); alreadyCast.push_back(spell); }
    virtual BOOL canCastSpell(const char* spell);

public:
    void resetSpells() {alreadyCast.clear(); }

    std::string buffer;
    std::list<std::string> alreadyCast;
};

