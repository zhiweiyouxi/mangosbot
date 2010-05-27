#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiInventoryManager.h"
#include "AiTargetManager.h"

namespace ai
{
    class MockAiInventoryManager : public AiInventoryManager
    {
    public:
        MockAiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiInventoryManager(ai, aiRegistry) 
        {
			this->buffer = buffer;
			hasDrink = hasFood = true;
			lootAvailable = false;
		}

	public:
		virtual void UseHealingPotion() { buffer->append(">hp"); }
		virtual void UseManaPotion() { buffer->append(">mp"); }
		virtual void UsePanicPotion() { buffer->append(">pp"); }
		virtual void UseFood() { buffer->append(">eat"); }
		virtual void UseDrink() { buffer->append(">drink"); }
		virtual bool HasFood() { return hasFood; }
		virtual bool HasDrink() { return hasDrink; }
		virtual bool HasHealingPotion() { return false; }
		virtual bool HasManaPotion() { return false; }
		virtual bool HasPanicPotion() { return false; }
		virtual int GetItemCount(const char* name)  { return itemCounts[std::string(name)]; }
		virtual bool FindAndUse(const char* item, uint8 ignore_time = 0) { buffer->append(">").append(item); return true; }
		virtual bool CanLoot() { return lootAvailable; }
		virtual void DoLoot() { buffer->append(">loot"); }

	private:
		string *buffer;

	public:
		bool hasDrink, hasFood;
		bool lootAvailable;
		std::map<string, int> itemCounts;
    };

}