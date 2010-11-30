#pragma once

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;
    class LootObjectStack;
    class LootObject;

	enum LootStrategy 
	{
		LOOTSTRATEGY_QUEST = 1,
		LOOTSTRATEGY_NORMAL = 2,
		LOOTSTRATEGY_ALL = 3
	};

	class LootManager
	{
	public:
        LootManager(Player* bot);
        virtual ~LootManager();

	public:
		virtual void ClearLoot();
        virtual void AddLoot(uint64 guid);
		virtual void AddLootItem(uint32 itemid);
		virtual void RemoveLootItem(uint32 itemid);
		virtual bool CanLoot();
		virtual void DoLoot();
		void SetLootStrategy(string strategy);
		string GetLootStrategy();
		set<uint32> lootItems;

	private:
        void DoLoot(LootObject &lootObject);
        void AddMasterSelection();
        void StoreLootItems(LootObject &lootObject);
        void ReleaseLoot();
		Item* StoreItem(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem);
        void NotifyLootItemRemoved(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem );
        void StoreLootItem(LootObject &loot, uint32 lootIndex);
        void StoreLockedLootItem(GameObject* go, LootItem * item, Loot* loot);
        void DeactivateLootGameObject(LootObject &lootObject);
		bool IsLootAllowed(LootItem * item);

	private:
        Player* bot;
		LootObjectStack *availableLoot;
		uint64 currentLoot;
		LootStrategy lootStrategy;
	};

};