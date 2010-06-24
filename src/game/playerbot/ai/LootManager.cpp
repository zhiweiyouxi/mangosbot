#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

void LootManager::ClearLoot()
{
	availableLoot.clear();
	currentLoot = 0;
}

void LootManager::AddLoot(uint64 guid)
{
	for (list<uint64>::iterator i = availableLoot.begin(); i != availableLoot.end(); i++)
	{
		if (*i == guid) 
			return;
	}

	availableLoot.push_front( guid );
	int lootSize = availableLoot.size();
	for (; lootSize>50; lootSize--) 
		availableLoot.pop_back();
}

bool LootManager::CanLoot()
{
	return !availableLoot.empty();
}

uint64 LootManager::FindNewLoot() 
{
    uint64 guid = 0;

    if (!availableLoot.empty())
    {
        guid = availableLoot.front();
        availableLoot.pop_front();
    }

    return guid;
}

WorldObject* LootManager::GetLootObject(Loot **loot)
{
    Creature *creature = bot->GetMap()->GetCreature(currentLoot);
    if (creature && creature->getDeathState() == CORPSE)
    {
        *loot = &creature->loot;
        return creature;
    }

    GameObject* gameObject = bot->GetMap()->GetGameObject(currentLoot);
    if (gameObject)
    {
        *loot = &gameObject->loot;
        return gameObject;
    }

    return NULL;
}

void LootManager::StoreLootItems(Loot* loot) 
{
    uint32 lootNum = loot->GetMaxSlotInLootFor(bot);
    for( uint32 l=0; l<lootNum; l++ )
    {
        StoreLootItem(loot, l);

    }
}

void LootManager::ReleaseLoot()
{
    if( uint64 lguid = bot->GetLootGUID() && bot->GetSession() )
        bot->GetSession()->DoLootRelease( lguid );
}

void LootManager::DeactivateLootGameObject()
{
    GameObject* go = bot->GetMap()->GetGameObject(currentLoot);
    if(go)
    {
        go->SetLootState(GO_JUST_DEACTIVATED);
        go->Update(0);
    }
}


void LootManager::DoLoot()
{
    if (!currentLoot)
    {
        Player* master = bot->GetPlayerbotAI()->GetMaster();
        uint64 guid = master->GetSelection();
        if (guid) AddLoot(guid);
    }

    while (CanLoot())
    {
        if (!currentLoot)
            currentLoot = FindNewLoot();

        if (!currentLoot)
            break;

        Loot* loot;
        WorldObject *wo = GetLootObject(&loot);
        if (!wo)
        {
            currentLoot = 0;
            continue;
        }

        float distance = bot->GetDistance(wo);
        if (distance > INTERACTION_DISTANCE && distance < BOTLOOT_DISTANCE)
        {
            bot->GetPlayerbotAI()->GetAiRegistry()->GetMoveManager()->MoveTo(wo->GetMapId(), wo->GetPositionX(), wo->GetPositionY(), wo->GetPositionZ());
            break;
        }

        bot->GetMotionMaster()->Clear();
	    bot->SendLoot(currentLoot, LOOT_CORPSE);

        StoreLootItems(loot);
        ReleaseLoot();

        if (!loot->unlootedCount)
            DeactivateLootGameObject();

        currentLoot = 0;
        break;
    }
}

void LootManager::StoreQuestItem( LootItem * item, QuestItem * qitem, Loot* loot, uint32 lootIndex, QuestItem * ffaitem, QuestItem * conditem )
{
    ItemPosCountVec dest;
    if( bot->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, item->itemid, item->count ) != EQUIP_ERR_OK )
        return;

    Item * newitem = bot->StoreNewItem( dest, item->itemid, true, item->randomPropertyId);

    if( qitem )
    {
        qitem->is_looted = true;
        if( item->freeforall || loot->GetPlayerQuestItems().size() == 1 )
            bot->SendNotifyLootItemRemoved( lootIndex );
        else
            loot->NotifyQuestItemRemoved( qitem->index );
    }
    else
    {
        if( ffaitem )
        {
            ffaitem->is_looted=true;
            bot->SendNotifyLootItemRemoved( lootIndex );
        }
        else
        {
            if( conditem )
                conditem->is_looted=true;
            loot->NotifyItemRemoved( lootIndex );
        }
    }
    if (!item->freeforall)
        item->is_looted = true;
    --loot->unlootedCount;
    bot->SendNewItem( newitem, uint32(item->count), false, false, true );
    bot->GetAchievementMgr().UpdateAchievementCriteria( ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM, item->itemid, item->count );
}

void LootManager::StoreLootItem(Loot* loot, uint32 lootIndex)
{
    QuestItem *qitem=0, *ffaitem=0, *conditem=0;
    LootItem *item = loot->LootItemInSlot( lootIndex, bot, &qitem, &ffaitem, &conditem );
    if( !item )
        return;

    if( !qitem && item->is_blocked )
    {
        bot->SendLootRelease( bot->GetLootGUID() );
        return;
    }

    if (item->AllowedForPlayer(bot) && item->needs_quest)
        StoreQuestItem(item, qitem, loot, lootIndex, ffaitem, conditem);

    GameObject* go = bot->GetMap()->GetGameObject(currentLoot);
    if(go)
        StoreGameObjectLootItem(go, item, loot);
}

void LootManager::StoreGameObjectLootItem( GameObject* go, LootItem * item, Loot* loot )
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
