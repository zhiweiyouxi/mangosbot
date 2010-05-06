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
            balancePercent = 100;
            targetIsMoving = false;
            targetIsCastingNonMeleeSpell = false;
            haveTarget = true;
			hasDrink = hasFood = true;
        }

        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f) { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer.append(">master"); }
        virtual void Flee(float distance = SPELL_DISTANCE) { buffer.append(">flee"); }
        virtual void Melee() { buffer.append(">melee"); }
        virtual void FollowMaster() { buffer.append(">follow"); }
        virtual void GoAway(float distance = SPELL_DISTANCE) { buffer.append(">goaway"); }
        virtual void Stay() { buffer.append(">stay"); }
        virtual bool CastSpell(const char* spell, Unit* target = NULL);
        virtual bool CastSpellOnCurrentTarget(const char* spell);
        virtual bool canCastSpell(const char* spell);
        virtual void MoveToTarget(float distance = 0.0f) {if (distance == SPELL_DISTANCE) buffer.append(">reach spell"); else buffer.append(">reach melee"); }
        virtual uint8 GetRage() { return rage; } 
        virtual bool HasAura(const char* spell);
        virtual bool TargetHasAura(const char* spell);
        virtual bool PetHasAura(const char* spell);
        virtual bool IsAllPartyHasAura(const char* spell);
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return (Player*)0xEEEEEE; }
        virtual uint8 GetHealthPercent() { return health; }
        virtual uint8 GetComboPoints() { return comboPoints; }
        virtual uint8 GetTargetHealthPercent() { return targetHealth; }
        virtual uint8 GetManaPercent() {return mana; }
        virtual bool HasAggro() { return aggro; }
        virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE) { return attackerCount; }
        virtual int GetMyAttackerCount() {return myAttackerCount; }
        virtual void RemoveAura(const char* name) {auras.remove(name); buffer.append(">-").append(name); }
        virtual bool CanLoot() { return lootAvailable; }
        virtual void Loot() { buffer.append(">loot"); }
        
        virtual void UseHealingPotion() { buffer.append(">hp"); }
        virtual void UseManaPotion() { buffer.append(">mp"); }
        virtual void UsePanicPotion() { buffer.append(">pp"); }
        virtual void UseFood() { buffer.append(">eat"); }
        virtual void UseDrink() { buffer.append(">drink"); }
        virtual bool HasFood() { return hasFood; }
        virtual bool HasDrink() { return hasDrink; }


        virtual uint8 GetPetHealthPercent() { return petHealth; }
        virtual bool HasPet() { return hasPet; }
        virtual bool IsPetDead() { return petHealth <= 0; }

        virtual bool IsMounted() { return FALSE; }
        virtual bool HaveTarget() { return haveTarget; }

        virtual bool HasHealingPotion() { return FALSE; }
        virtual bool HasManaPotion() { return FALSE; }
        virtual bool HasPanicPotion() { return FALSE; }

        virtual void AttackLeastThreat() {buffer.append(">attack least threat"); }
        virtual void AttackBiggerThreat() {buffer.append(">attack bigger threat"); }

        virtual Player* GetPartyMinHealthPlayer() { return (Player*)0xEEEEEE; }
        virtual uint8 GetPartyMinHealthPercent() { return partyMinHealth; }
        virtual void TellMaster(const char* text) { buffer.append(text); }

        virtual void Emote(uint32 emote) { buffer.append(">emote"); }
        virtual float GetFollowAngle() { return 0; }
        virtual bool HasSpell(const char* spell) { return TRUE; }

        virtual Player* GetPartyMemberToDispell(uint32 dispelType) { return partyAurasToDispel == dispelType ? (Player*)0xEEEEEE : NULL; }
        virtual bool HasAuraToDispel(uint32 dispelType) { return aurasToDispel == dispelType; }
        virtual float GetBalancePercent() { return balancePercent; }
        virtual bool IsTargetMoving() { return targetIsMoving; }
        virtual bool IsTargetCastingNonMeleeSpell() { return targetIsCastingNonMeleeSpell; }
        virtual bool TargetHasAuraToDispel(uint32 dispelType) { return targetAurasToDispel == dispelType; }

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
        bool aggro;
        bool hasPet;
        int attackerCount;
        int myAttackerCount;
        int partyMinHealth;
        bool lootAvailable;
        uint32 partyAurasToDispel, aurasToDispel, targetAurasToDispel;
        float balancePercent;
        bool targetIsMoving;
        bool targetIsCastingNonMeleeSpell;
        bool haveTarget;
		bool hasDrink, hasFood;
    };

}