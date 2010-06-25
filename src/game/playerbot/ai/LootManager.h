#pragma once

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;
    class LootObjectStack;
    class LootObject;

	class LootManager
	{
	public:
        LootManager(Player* bot);
        virtual ~LootManager();

	public:
		virtual void ClearLoot();
        virtual void AddLoot(uint64 guid);
		virtual bool CanLoot();
		virtual void DoLoot();

	private:
        void DoLoot(LootObject &lootObject);
        void AddMasterSelection();
        void StoreLootItems(LootObject &lootObject);
        void ReleaseLoot();
        void StoreQuestItem(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem );
        void StoreLootItem(LootObject &loot, uint32 lootIndex);
        void StoreGameObjectLootItem( GameObject* go, LootItem * item, Loot* loot );
        void DeactivateLootGameObject(LootObject &lootObject);

	private:
        Player* bot;
		LootObjectStack *availableLoot;
		uint64 currentLoot;
	};

};