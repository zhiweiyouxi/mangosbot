#pragma once

#include "PlayerbotAIFacade.h"
#include "string"
#include "MockAiStatsManager.h"
#include "MockAiSpellManager.h"
#include "MockAiTargetManager.h"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade, PlayerbotAIBase
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL), PlayerbotAIBase(NULL, NULL)
        { 
			statsManager = new MockAiStatsManager(this);
			spellManager = new MockAiSpellManager(this, &buffer);
			targetManager = new MockAiTargetManager(this, spellManager, statsManager);

            distanceToEnemy = 15.0f; aggro = TRUE; 
            attackerCount = 1;myAttackerCount = 1;
            lootAvailable = false;
            balancePercent = 100;
            targetIsMoving = false;
            haveTarget = true;
			hasDrink = hasFood = true;
        }

		AiSpellManager* GetSpellManager() { return spellManager; }
		AiTargetManager* GetTargetManager() { return targetManager; }
		AiStatsManager* GetStatsManager() { return statsManager; }

        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f) { return distanceToEnemy; }
        virtual void MoveToMaster() { buffer.append(">master"); }
        virtual bool Flee(float distance = SPELL_DISTANCE) { buffer.append(">flee"); return true; }
        virtual void Melee() { buffer.append(">melee"); }
        virtual void FollowMaster() { buffer.append(">follow"); }
        virtual void GoAway(float distance = SPELL_DISTANCE) { buffer.append(">goaway"); }
        virtual void Stay() { buffer.append(">stay"); }
		virtual void MoveToTarget(float distance = 0.0f) {if (distance == SPELL_DISTANCE) buffer.append(">reach spell"); else buffer.append(">reach melee"); }
        virtual bool HasAggro() { return aggro; }
        virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE) { return attackerCount; }
        virtual int GetMyAttackerCount() {return myAttackerCount; }
        virtual bool CanLoot() { return lootAvailable; }
        virtual void Loot() { buffer.append(">loot"); }
        
        virtual void UseHealingPotion() { buffer.append(">hp"); }
        virtual void UseManaPotion() { buffer.append(">mp"); }
        virtual void UsePanicPotion() { buffer.append(">pp"); }
        virtual void UseFood() { buffer.append(">eat"); }
        virtual void UseDrink() { buffer.append(">drink"); }
        virtual bool HasFood() { return hasFood; }
        virtual bool HasDrink() { return hasDrink; }
		virtual int GetItemCount(const char* name)  { return itemCounts[std::string(name)]; }



        virtual bool IsMounted() { return FALSE; }
        virtual bool HaveTarget() { return haveTarget; }

        virtual bool HasHealingPotion() { return FALSE; }
        virtual bool HasManaPotion() { return FALSE; }
        virtual bool HasPanicPotion() { return FALSE; }

        virtual void AttackLeastThreat() {buffer.append(">attack least threat"); }
        virtual void AttackBiggerThreat() {buffer.append(">attack bigger threat"); }

        virtual void TellMaster(const char* text) { buffer.append(text); }

        virtual void Emote(uint32 emote) { buffer.append(">emote"); }
        virtual float GetFollowAngle() { return 0; }
        virtual bool HasSpell(const char* spell) { return TRUE; }

        virtual float GetBalancePercent() { return balancePercent; }
        virtual bool IsTargetMoving() { return targetIsMoving; }

		virtual bool FindAndUse(const char* item, uint8 ignore_time = 0) { buffer.append(">").append(item); return true; }

        std::string buffer;
        //std::list<std::string> spellCooldowns;
        //std::list<std::string> auras;
        //std::list<std::string> partyAuras;
        //std::list<std::string> targetAuras;
        //std::list<std::string> petAuras;
        float distanceToEnemy;
        //uint8 rage, mana;
        //uint8 targetMana;
		//uint8 petHealth;
        bool aggro;
        int attackerCount;
        int myAttackerCount;
        //int partyMinHealth;
        bool lootAvailable;
        //uint32 partyAurasToDispel, aurasToDispel, targetAurasToDispel;
        float balancePercent;
        bool targetIsMoving;
        //bool targetIsCastingNonMeleeSpell;
        bool haveTarget;
		bool hasDrink, hasFood;
		std::map<string, int> itemCounts;
		//bool deadPartyMember;
		//uint32 energy;
    
		AiSpellManager* spellManager;
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
	};

}