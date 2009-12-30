#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL) { distanceToEnemy = 100.0f; }

        virtual float GetDistanceToEnemy() { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer = buffer.append(">flee"); }
        virtual void CastSpell(const char* spell) { buffer.append(">").append(spell); alreadyCast.push_back(spell); }
        virtual BOOL canCastSpell(const char* spell);
        virtual void MoveToTarget() {buffer.append(">melee"); }

    public:
        void resetSpells() {alreadyCast.clear(); }
        void resetSpell(const char* spell);

        std::string buffer;
        std::list<std::string> alreadyCast;
        float distanceToEnemy;
    };

}