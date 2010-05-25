#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "Item.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;

	class AiInventoryManager : public AiManagerBase
	{
	public:
		AiInventoryManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
			currentLoot = 0;
		}

	public:
		virtual void UseHealingPotion() { FindAndUse(isHealingPotion); }
		virtual void UseManaPotion() { FindAndUse(isManaPotion); }
		virtual void UsePanicPotion()  { FindAndUse(isPanicPotion); }
		virtual void UseFood();
		virtual void UseDrink();
		virtual bool HasFood() { return FindUsableItem(isFood) != NULL; }
		virtual bool HasDrink() { return FindUsableItem(isDrink) != NULL; }
		virtual bool HasHealingPotion() { return FindUsableItem(isHealingPotion) != NULL; }
		virtual bool HasManaPotion() { return FindUsableItem(isManaPotion) != NULL; }
		virtual bool HasPanicPotion() { return FindUsableItem(isPanicPotion) != NULL; }
		virtual int GetItemCount(const char* name);
		virtual bool FindAndUse(const char* item, uint8 ignore_time = 0)
		{
			return FindAndUse(isTheSameName, (const void*)item, ignore_time);
		}
		virtual void ClearLoot();
		virtual void AddLoot(uint64 guid);
		virtual bool CanLoot();
		virtual void DoLoot();

	private:
		Item* FindUsableItem(bool predicate(const ItemPrototype*, const void*), const void* param = NULL, int *count=NULL);
		static bool isHealingPotion(const ItemPrototype* pItemProto, const void* param);
		static bool isManaPotion(const ItemPrototype* pItemProto, const void* param);
		static bool isPanicPotion(const ItemPrototype* pItemProto, const void* param);
		static bool isFood(const ItemPrototype* pItemProto, const void* param);
		static bool isDrink(const ItemPrototype* pItemProto, const void* param);
		static bool isTheSameName(const ItemPrototype* pItemProto, const void* param);
		virtual bool FindAndUse(bool predicate(const ItemPrototype*, const void*), const void* param = NULL, uint8 ignore_time = 0);
		void UseItem(Item& item);

	private:
		list<uint64> availableLoot;
		uint64 currentLoot;
	};

};