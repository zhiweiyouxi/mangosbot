#pragma once

using namespace std;

namespace ai 
{
    class LootObject
    {
    public:
        LootObject() {}
        LootObject(Player* bot, uint64 guid);
        LootObject(const LootObject& other);

    public:
        bool IsEmpty() { return !worldObject || !loot; }
        WorldObject* worldObject;
        Loot* loot;
        uint64 guid;
    };

    class LootObjectStack
    {
    public:
        LootObjectStack(Player* bot);

    public:
        void Add(uint64 guid);
        void Remove(uint64 guid);
        void Clear();
        bool CanLoot(float maxDistance);
        LootObject GetLoot(float maxDistance = 0);

    private:
        vector<LootObject> OrderByDistance(float maxDistance = 0);

    private:
        Player* bot;
        set<uint64> availableLoot;
    };

};