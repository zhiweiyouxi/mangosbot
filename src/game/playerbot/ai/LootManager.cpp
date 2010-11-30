#include "../../pchdef.h"
#include "LootObjectStack.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

LootManager::LootManager(Player* bot)
{
    availableLoot = new LootObjectStack(bot);
    this->bot = bot;
	lootStrategy = LOOTSTRATEGY_NORMAL;
}

LootManager::~LootManager()
{
    delete availableLoot;
}

void LootManager::ClearLoot()
{
	availableLoot->Clear();
}

void LootManager::AddLoot(uint64 guid)
{
	availableLoot->Add(guid);
}

bool LootManager::CanLoot()
{
    return availableLoot->CanLoot(BOTLOOT_DISTANCE);
}

void LootManager::StoreLootItems(LootObject &lootObject) 
{
    bot->SendLoot(lootObject.guid, LOOT_CORPSE);

    uint32 lootNum = lootObject.loot->GetMaxSlotInLootFor(bot);
    for( uint32 l=0; l<lootNum; l++ )
        StoreLootItem(lootObject, l);

    if (lootObject.loot->isLooted())
        DeactivateLootGameObject(lootObject);

    ReleaseLoot();
}

void LootManager::ReleaseLoot()
{
    if( uint64 lguid = bot->GetLootGUID() && bot->GetSession() )
        bot->GetSession()->DoLootRelease( lguid );
}

void LootManager::DeactivateLootGameObject(LootObject &loot)
{
    GameObject* go = bot->GetMap()->GetGameObject(loot.guid);
    if(go)
    {
        go->SetLootState(GO_JUST_DEACTIVATED);
        go->Update(0);
    }
}


void LootManager::DoLoot()
{
    bot->GetMotionMaster()->Clear();

    AddMasterSelection();

    if (CanLoot())
    {
        LootObject lootObject = availableLoot->GetLoot(BOTLOOT_DISTANCE);
        DoLoot(lootObject);
    }
}

void LootManager::DoLoot(LootObject &lootObject)
{
    float distance = bot->GetDistance(lootObject.worldObject);
    if (distance > INTERACTION_DISTANCE)
    {
        bot->GetPlayerbotAI()->GetAiRegistry()->GetMoveManager()->MoveTo(lootObject.worldObject);
        return;
    }

    StoreLootItems(lootObject);
    availableLoot->Remove(lootObject.guid);
}

Item* LootManager::StoreItem( LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem )
{
    ItemPosCountVec dest;
    if( bot->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, item->itemid, item->count ) != EQUIP_ERR_OK )
        return NULL;

    Item * newitem = bot->StoreNewItem( dest, item->itemid, true, item->randomPropertyId);
	if (!newitem)
		return NULL;

	bot->SendNewItem( newitem, uint32(item->count), false, false, true );
	bot->GetAchievementMgr().UpdateAchievementCriteria( ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM, item->itemid, item->count );

	ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(item->itemid);
	bot->GetPlayerbotAI()->GetAiRegistry()->GetInventoryManager()->QueryItemUsage(proto);
	bot->GetPlayerbotAI()->GetAiRegistry()->GetQuestManager()->QueryQuestItem(item->itemid);

	NotifyLootItemRemoved(item, qitem, loot, lootIndex, ffaitem, conditem);

	return newitem;
}

void LootManager::NotifyLootItemRemoved(LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem )
{
    if (qitem)
    {
        qitem->is_looted = true;
        if( item->freeforall || loot->GetPlayerQuestItems().size() == 1 )
            bot->SendNotifyLootItemRemoved( lootIndex );
        else
            loot->NotifyQuestItemRemoved( qitem->index );
    }
    else if (ffaitem)
    {
        ffaitem->is_looted=true;
        bot->SendNotifyLootItemRemoved( lootIndex );
    }
    else
    {
        if(conditem)
            conditem->is_looted=true;
        loot->NotifyItemRemoved( lootIndex );
    }
    
    if (!item->freeforall)
        item->is_looted = true;

    --loot->unlootedCount;
}

void LootManager::StoreLootItem(LootObject &lootObject, uint32 lootIndex)
{
    Loot* loot = lootObject.loot;
    QuestItem *qitem=0, *ffaitem=0, *conditem=0;
    LootItem *item = loot->LootItemInSlot( lootIndex, bot, &qitem, &ffaitem, &conditem );
    if( !item )
        return;

    if( !qitem && item->is_blocked )
        return;

	if (IsLootAllowed(item))
        StoreItem(item, qitem, loot, lootIndex, ffaitem, conditem);

    GameObject* go = bot->GetMap()->GetGameObject(lootObject.guid);
    if(go)
        StoreLockedLootItem(go, item, loot);
}

void LootManager::StoreLockedLootItem( GameObject* go, LootItem * item, Loot* loot )
{
    if ( !go->isSpawned() )
        return;

    uint32 lockId = go->GetGOInfo()->GetLockId();
    LockEntry const *lockInfo = sLockStore.LookupEntry(lockId);
    if(!lockInfo)
        return;

    uint32 skillId = 0;
    uint32 reqSkillValue = 0;
    for(int i = 0; i < 8; ++i)
    {
        skillId = SkillByLockType(LockType(lockInfo->Index[i]));
        if(skillId > 0)
        {
            reqSkillValue = lockInfo->Skill[i];
            break;
        }
    }

    if (skillId != SKILL_NONE && !bot->HasSkill(skillId))
        return;

    ItemPosCountVec dest;
    if (bot->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, item->itemid, item->count) != EQUIP_ERR_OK)
        return;

    Item* pItem = bot->StoreNewItem (dest,item->itemid,true,item->randomPropertyId);
    uint32 SkillValue = bot->GetPureSkillValue(skillId);
    if (SkillValue >= reqSkillValue)
    {
        bot->SendNewItem(pItem, uint32(item->count), false, false, true);
        bot->UpdateGatherSkill(skillId, SkillValue, reqSkillValue);
        --loot->unlootedCount;
    }
}

void LootManager::AddMasterSelection()
{
    uint64 masterSelection = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid().GetRawValue();
    if (masterSelection) 
        AddLoot(masterSelection);
}

void LootManager::SetLootStrategy(string strategy)
{
	if (strategy == "*" || strategy == "all")
		lootStrategy = LOOTSTRATEGY_ALL;
	else if (strategy == "q" || strategy == "quest")
		lootStrategy = LOOTSTRATEGY_QUEST;
	else 
		lootStrategy = LOOTSTRATEGY_NORMAL;
}

string LootManager::GetLootStrategy()
{
	switch (lootStrategy)
	{
	case LOOTSTRATEGY_ALL:
		return "all";
	case LOOTSTRATEGY_QUEST:
		return "quest";
	default:
		return "normal";
	}
}

bool LootManager::IsLootAllowed(LootItem * item) 
{
	if (!item->AllowedForPlayer(bot) || !item->is_blocked)
		return false;
	
	if (lootStrategy == LOOTSTRATEGY_ALL)
		return true;

	ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(item->itemid);
	if (!proto)
		return false;

	if (item->needs_quest || proto->Bonding == BIND_QUEST_ITEM || proto->Bonding == BIND_QUEST_ITEM1)
		return true;
		
	if (lootStrategy == LOOTSTRATEGY_QUEST)
		return false;

	if (proto->Bonding == BIND_WHEN_PICKED_UP)
		return false;

	if (item->freeforall || item->is_underthreshold)
		return true;

	return false;
}