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
            distanceToEnemy = 15.0f; rage = 0; aggro = TRUE; health = 100; mana = 100; partyMinHealth = 100; 
            targetHealth = 100; petHealth = 100; hasPet = TRUE;
            attackerCount = 1;myAttackerCount = 1;
            comboPoints = 0;
            lootAvailable = false;
        }

        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f) { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer.append(">master"); }
        virtual void Flee(float distance = SPELL_DISTANCE) { buffer.append(">flee"); }
        virtual void Melee() { buffer.append(">melee"); }
        virtual void FollowMaster() { buffer.append(">follow"); }
        virtual void GoAway(float distance = SPELL_DISTANCE) { buffer.append(">goaway"); }
        virtual void Stay() { buffer.append(">stay"); }
        virtual BOOL CastSpell(const char* spell, Unit* target = NULL);
        virtual BOOL canCastSpell(const char* spell);
        virtual void MoveToTarget(float distance = 0.0f) {if (distance) buffer.append(">reach spell"); else buffer.append(">reach melee"); }
        virtual uint8 GetRage() { return rage; } 
        virtual BOOL HasAura(const char* spell);
        virtual BOOL TargetHasAura(const char* spell);
        virtual BOOL PetHasAura(const char* spell);
        virtual BOOL IsAllPartyHasAura(const char* spell);
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return (Player*)0xEEEEEE; }
        virtual uint8 GetHealthPercent() { return health; }
        virtual uint8 GetComboPoints() { return comboPoints; }
        virtual uint8 GetTargetHealthPercent() { return targetHealth; }
        virtual uint8 GetManaPercent() {return mana; }
        virtual BOOL HasAggro() { return aggro; }
        virtual int GetAttackerCount() { return attackerCount; }
        virtual int GetMyAttackerCount() {return myAttackerCount; }
        virtual void RemoveAura(const char* name) {auras.remove(name); buffer.append(">-").append(name); }
        virtual bool CanLoot() { return lootAvailable; }
        virtual void Loot() { buffer.append(">loot"); }
        
        virtual void UseHealingPotion() { buffer.append(">hp"); }
        virtual void UseManaPotion() { buffer.append(">mp"); }
        virtual void UsePanicPotion() { buffer.append(">pp"); }
        virtual void UseFood() { buffer.append(">eat"); }
        virtual void UseDrink() { buffer.append(">drink"); }

        virtual uint8 GetPetHealthPercent() { return petHealth; }
        virtual BOOL HasPet() { return hasPet; }
        virtual BOOL IsPetDead() { return petHealth <= 0; }

        virtual BOOL IsMounted() { return FALSE; }
        virtual BOOL HaveTarget() { return FALSE; }

        virtual BOOL HasHealingPotion() { return FALSE; }
        virtual BOOL HasManaPotion() { return FALSE; }
        virtual BOOL HasPanicPotion() { return FALSE; }

        virtual void AttackLeastThreat() {buffer.append(">attack least threat"); }
        virtual void AttackBiggerThreat() {buffer.append(">attack bigger threat"); }

        virtual Player* GetPartyMinHealthPlayer() { return (Player*)0xEEEEEE; }
        virtual uint8 GetPartyMinHealthPercent() { return partyMinHealth; }
        virtual void TellMaster(const char* text) { buffer.append(text); }

        virtual void Emote(uint32 emote) { buffer.append(">emote"); }
        virtual float GetFollowAngle() { return 0; }
        virtual BOOL HasSpell(const char* spell) { return TRUE; }
    public:
        void resetSpells() {spellCooldowns.clear(); }

        std::string buffer;
        std::list<std::string> spellCooldowns;
        std::list<std::string> auras;
        std::list<std::string> partyAuras;
        std::list<std::string> targetAuras;
        std::list<std::string> petAuras;
        float distanceToEnemy;
        uint8 rage, health, mana;
        uint8 targetHealth, petHealth;
        uint8 comboPoints;
        BOOL aggro;
        BOOL hasPet;
        int attackerCount;
        int myAttackerCount;
        int partyMinHealth;
        bool lootAvailable;
    };

}