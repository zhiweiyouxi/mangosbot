#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL) { distanceToEnemy = 15.0f; rage = 0; aggro = TRUE; attackerCount = 1; }

        virtual float GetDistanceToEnemy() { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer = buffer.append(">flee"); }
        virtual void CastSpell(const char* spell) { buffer.append(">").append(spell); alreadyCast.push_back(spell); }
        virtual BOOL canCastSpell(const char* spell);
        virtual void MoveToTarget(float distance = 0.0f) {if (distance) buffer.append(">reach spell"); else buffer.append(">melee"); }
        virtual uint8 GetRage() { return rage; } 
        virtual BOOL HasAura(const char* spell);
        virtual uint8 GetHealthPercent() { return health; }
        virtual uint8 GetManaPercent() { return mana; }
        virtual BOOL HasAggro() { return aggro; }
        virtual int GetAttackerCount() { return attackerCount; }
        virtual void RemoveAura(const char* name) {auras.remove(name); buffer.append(">-").append(name); }
        
        virtual void UseHealingPotion() { buffer.append(">hp"); }
        virtual void UseManaPotion() { buffer.append(">mp"); }
        virtual void UsePanicPotion() { buffer.append(">pp"); }

        virtual BOOL HasHealingPotion() { return FALSE; }
        virtual BOOL HasManaPotion() { return FALSE; }
        virtual BOOL HasPanicPotion() { return FALSE; }

    public:
        void resetSpells() {alreadyCast.clear(); }
        void resetSpell(const char* spell);

        std::string buffer;
        std::list<std::string> alreadyCast;
        std::list<std::string> auras;
        float distanceToEnemy;
        uint8 rage, health, mana;
        BOOL aggro;
        int attackerCount;
    };

}