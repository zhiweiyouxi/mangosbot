#pragma once

#include "strategy/actions/InventoryAction.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;
using ai::InventoryAction;

class PlayerbotFactory : public InventoryAction
{
public:
    PlayerbotFactory(Player* bot, uint32 level) : bot(bot), level(level), InventoryAction(bot->GetPlayerbotAI(), "factory") {}

    static ObjectGuid GetRandomBot();
    void Randomize();
    void RandomizeForZone(uint32 mapId, float teleX, float teleY, float teleZ);

private:
    void InitEquipment();
    bool CanEquipUnseenItem(uint8 slot, uint16 &dest, uint32 item);
    bool EquipItem(uint8 slot, uint32 desiredQuality);
    void InitSkills();
    void SetRandomSkill(uint16 id);
    void InitSpells();
    void InitAvailableSpells();
    void InitTalents();
    void InitTalents(uint32 specNo);
    void InitQuests();
    void InitPet();
    void ClearInventory();
    void InitAmmo();

private:
    Player* bot;
    uint32 level;
};
