#pragma once
#include "LootManager.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;

	class AiInventoryManager : public AiManagerBase
	{
	public:
		AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry);
        virtual ~AiInventoryManager();

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
		
        virtual void ClearLoot() { lootManager->ClearLoot(); }
        virtual void AddLoot(uint64 guid) { lootManager->AddLoot(guid); }
        virtual bool CanLoot() { return lootManager->CanLoot(); }
        virtual void DoLoot() { lootManager->DoLoot(); }
		
        virtual void EquipItem(const char* link);
		virtual void UseItem(const char* link);
		virtual void Reward(const char* link);
		virtual void ItemLocalization(std::string& itemName, const uint32 itemID);
		virtual void extractItemIds(const string& text, list<uint32>& itemIds);
		virtual void findItemsInInv(list<uint32>& itemIdSearchList, list<Item*>& foundItemList);
		virtual void findItemsInEquip(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList);
		virtual void ListQuestItems();

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
        virtual void HandleMasterIncomingPacket(const WorldPacket& packet);
        virtual void Query(const string& text);

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
		void EquipItem(Item& item);
        void QueryItemUsage(ItemPrototype const *item);
        void QueryItemsUsage(list<uint32> items);
        void UseGameObject(uint64 guid);

	private:
        LootManager *lootManager;
	};

};