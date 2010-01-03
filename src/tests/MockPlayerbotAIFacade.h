#pragma once

#include "PlayerbotAIFacade.h"
#include "string"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL) 
        { 
            distanceToEnemy = 15.0f; rage = 0; aggro = TRUE; attackerCount = 1; health = 100; mana = 100; partyMinHealth = 100; 
            targetHealth = 100;
        }

        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f) { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer.append(">master"); }
        virtual void Flee(float distance = SPELL_DISTANCE) { buffer.append(">flee"); }
        virtual void FollowMaster() { buffer.append(">follow"); }
        virtual void Stay() { buffer.append(">stay"); }
        virtual void CastSpell(const char* spell, Unit* target = NULL) { buffer.append(">").append(spell); alreadyCast.push_back(spell); if (target) buffer.append(" on party"); }
        virtual BOOL canCastSpell(const char* spell);
        virtual void MoveToTarget(float distance = 0.0f) {if (distance) buffer.append(">reach spell"); else buffer.append(">melee"); }
        virtual uint8 GetRage() { return rage; } 
        virtual BOOL HasAura(const char* spell);
        virtual BOOL TargetHasAura(const char* spell);
        virtual BOOL IsAllPartyHasAura(const char* spell);
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return (Player*)0xEEEEEE; }
        virtual uint8 GetHealthPercent() { return health; }
        virtual uint8 GetTargetHealthPercent() { return targetHealth; }
        virtual uint8 GetManaPercent() {return mana; }
        virtual BOOL HasAggro() { return aggro; }
        virtual int GetAttackerCount() { return attackerCount; }
        virtual void RemoveAura(const char* name) {auras.remove(name); buffer.append(">-").append(name); }
        
        virtual void UseHealingPotion() { buffer.append(">hp"); }
        virtual void UseManaPotion() { buffer.append(">mp"); }
        virtual void UsePanicPotion() { buffer.append(">pp"); }
        virtual void UseFood() { buffer.append(">eat"); }
        virtual void UseDrink() { buffer.append(">drink"); }

        virtual BOOL HasHealingPotion() { return FALSE; }
        virtual BOOL HasManaPotion() { return FALSE; }
        virtual BOOL HasPanicPotion() { return FALSE; }

        virtual Player* GetPartyMinHealthPlayer() { return (Player*)0xEEEEEE; }
        virtual uint8 GetPartyMinHealthPercent() { return partyMinHealth; }

    public:
        void resetSpells() {alreadyCast.clear(); }
        void resetSpell(const char* spell);

        std::string buffer;
        std::list<std::string> alreadyCast;
        std::list<std::string> auras;
        std::list<std::string> partyAuras;
        std::list<std::string> targetAuras;
        float distanceToEnemy;
        uint8 rage, health, mana;
        uint8 targetHealth;
        BOOL aggro;
        int attackerCount;
        int partyMinHealth;
    };

}