#pragma once

#include "PlayerbotAIFacade.h"
#include "string"
#include "MockAiStatsManager.h"
#include "MockAiSpellManager.h"
#include "MockAiTargetManager.h"
#include "MockAiMoveManager.h"
#include "MockAiManagerRegistry.h"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade, PlayerbotAIBase
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL), PlayerbotAIBase(NULL, NULL)
        { 
			aiRegistry = new MockAiManagerRegistry(this, &buffer);

            lootAvailable = false;
			hasDrink = hasFood = true;
        }

		virtual ~MockPlayerbotAIFacade() 
		{
			delete aiRegistry;
		}

		AiSpellManager* GetSpellManager() { return aiRegistry->GetSpellManager(); }
		AiTargetManager* GetTargetManager() { return aiRegistry->GetTargetManager(); }
		AiStatsManager* GetStatsManager() { return aiRegistry->GetStatsManager(); }
		AiMoveManager* GetMoveManager() { return aiRegistry->GetMoveManager(); }

        virtual void Melee() { buffer.append(">melee"); }
        virtual void Attack(Unit* target);
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

        virtual bool HasHealingPotion() { return FALSE; }
        virtual bool HasManaPotion() { return FALSE; }
        virtual bool HasPanicPotion() { return FALSE; }

        virtual void AttackLeastThreat() {buffer.append(">attack least threat"); }
        virtual void AttackBiggerThreat() {buffer.append(">attack bigger threat"); }

        virtual void TellMaster(const char* text) { buffer.append(text); }

        virtual void Emote(uint32 emote) { buffer.append(">emote"); }
        virtual float GetFollowAngle() { return 0; }
        virtual bool HasSpell(const char* spell) { return TRUE; }

		virtual bool FindAndUse(const char* item, uint8 ignore_time = 0) { buffer.append(">").append(item); return true; }

        std::string buffer;
        //std::list<std::string> spellCooldowns;
        //std::list<std::string> auras;
        //std::list<std::string> partyAuras;
        //std::list<std::string> targetAuras;
        //std::list<std::string> petAuras;
        //float distanceToEnemy;
        //uint8 rage, mana;
        //uint8 targetMana;
		//uint8 petHealth;
        //int partyMinHealth;
        bool lootAvailable;
        //uint32 partyAurasToDispel, aurasToDispel, targetAurasToDispel;
        //bool targetIsMoving;
        //bool targetIsCastingNonMeleeSpell;
 		bool hasDrink, hasFood;
		std::map<string, int> itemCounts;
		//bool deadPartyMember;
		//uint32 energy;
    
		AiManagerRegistry* aiRegistry;
	};

}