#pragma once

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;

	class LootManager
	{
	public:
		LootManager(Player* bot)
		{
			currentLoot = 0;
            this->bot = bot;
		}

	public:
		virtual void ClearLoot();
		virtual void AddLoot(uint64 guid);
		virtual bool CanLoot();
		virtual void DoLoot();

	private:
        uint64 FindNewLoot();
        WorldObject* GetLootObject(Loot **loot);
        void StoreLootItems(Loot* loot);
        void ReleaseLoot();
        void StoreQuestItem( LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem );
        void StoreLootItem(Loot* loot, uint32 lootIndex);
        void StoreGameObjectLootItem( GameObject* go, LootItem * item, Loot* loot );

	private:
        Player* bot;
		list<uint64> availableLoot;
		uint64 currentLoot;
	};

};