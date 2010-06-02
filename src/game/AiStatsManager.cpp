#include "pchdef.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "AiStatsManager.h"
#include "AiSocialManager.h"
#include "AiStrategyManager.h"
#include "AiManagerRegistry.h"
#include "Spell.h"
#include "WorldPacket.h"

using namespace ai;
using namespace std;

uint8 AiStatsManager::GetHealthPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100;
}

uint8 AiStatsManager::GetRage(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_RAGE)));
}

uint8 AiStatsManager::GetEnergy(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_ENERGY)));
}

uint8 AiStatsManager::GetManaPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetPower(POWER_MANA)) / target->GetMaxPower(POWER_MANA)) * 100;
}

uint8 AiStatsManager::GetComboPoints(Player* target) 
{
    if (!target)
        return 0;
	return target->GetComboPoints();
}

bool AiStatsManager::HasMana(Unit* target)
{
    if (!target)
        return false;
	// TODO: base value?
	return target->GetPower(POWER_MANA);
}

bool AiStatsManager::IsDead(Unit* target)
{
    if (!target)
        return false;
	return target->getDeathState() != ALIVE; 
}

int AiStatsManager::GetMyAttackerCount()
{
    return bot->getAttackers().size();
}

bool AiStatsManager::HasAggro(Unit* target)
{
	if (!target)
		return true;

	HostileReference *ref = bot->getHostileRefManager().getFirst();
	if (!ref)
		return true; // simulate as target is not atacking anybody yet

	while( ref )
	{
		ThreatManager *threatManager = ref->getSource();
		Unit *attacker = threatManager->getOwner();
		Unit *victim = attacker->getVictim();
		if (victim == bot && target == attacker)
			return true;
		ref = ref->next();
	}
	return false;
}


bool AiStatsManager::IsMounted()
{
	return bot->IsMounted();
}


void AiStatsManager::ListStats()
{
	std::ostringstream out;

	uint32 totalused = 0;
	// list out items in main backpack
	for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
	{
		const Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
		if (pItem)
			totalused++;
	}
	uint32 totalfree = 16 - totalused;
	// list out items in other removable backpacks
	for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
	{
		const Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
		if (pBag)
		{
			ItemPrototype const* pBagProto = pBag->GetProto();
			if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
				totalfree =  totalfree + pBag->GetFreeSlots();
		}

	}

	// calculate how much money bot has
	uint32 copper = bot->GetMoney();
	uint32 gold = uint32(copper / 10000);
	copper -= (gold * 10000);
	uint32 silver = uint32(copper / 100);
	copper -= (silver * 100);

	out << "|cffffffff[|h|cff00ffff" << bot->GetName() << "|h|cffffffff]" << " has |r|cff00ff00" << gold
		<< "|r|cfffffc00g|r|cff00ff00" << silver
		<< "|r|cffcdcdcds|r|cff00ff00" << copper
		<< "|r|cffffd333c" << "|h|cffffffff bag slots |h|cff00ff00" << totalfree;

	// estimate how much item damage the bot has
	copper = EstRepairAll();
	gold = uint32(copper / 10000);
	copper -= (gold * 10000);
	silver = uint32(copper / 100);
	copper -= (silver * 100);

	out << "|h|cffffffff & item damage cost " << "|r|cff00ff00" << gold
		<< "|r|cfffffc00g|r|cff00ff00" << silver
		<< "|r|cffcdcdcds|r|cff00ff00" << copper
		<< "|r|cffffd333c";

	aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
}


uint32 AiStatsManager::EstRepairAll()
{
	uint32 TotalCost = 0;
	// equipped, backpack, bags itself
	for(int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
		TotalCost += EstRepair(( (INVENTORY_SLOT_BAG_0 << 8) | i ));

	// bank, buyback and keys not repaired

	// items in inventory bags
	for(int j = INVENTORY_SLOT_BAG_START; j < INVENTORY_SLOT_BAG_END; ++j)
		for(int i = 0; i < MAX_BAG_SIZE; ++i)
			TotalCost += EstRepair(( (j << 8) | i ));
	return TotalCost;
}

uint32 AiStatsManager::EstRepair(uint16 pos)
{
	Item* item = bot->GetItemByPos(pos);

	uint32 TotalCost = 0;
	if(!item)
		return TotalCost;

	uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
	if(!maxDurability)
		return TotalCost;

	uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

	uint32 LostDurability = maxDurability - curDurability;
	if(LostDurability>0)
	{
		ItemPrototype const *ditemProto = item->GetProto();

		DurabilityCostsEntry const *dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
		if(!dcost)
		{
			sLog.outError("RepairDurability: Wrong item lvl %u", ditemProto->ItemLevel);
			return TotalCost;
		}

		uint32 dQualitymodEntryId = (ditemProto->Quality+1)*2;
		DurabilityQualityEntry const *dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
		if(!dQualitymodEntry)
		{
			sLog.outError("RepairDurability: Wrong dQualityModEntry %u", dQualitymodEntryId);
			return TotalCost;
		}

		uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class,ditemProto->SubClass)];
		uint32 costs = uint32(LostDurability*dmultiplier*double(dQualitymodEntry->quality_mod));

		if (costs==0)                                   //fix for ITEM_QUALITY_ARTIFACT
			costs = 1;

		TotalCost = costs;
	}
	return TotalCost;
}

void AiStatsManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "stats")
	{
		ListStats();
	}    

}

void AiStatsManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{

}

bool AiStatsManager::IsTank(Player* player)
{
	PlayerbotAI* botAi = player->GetPlayerbotAI();
	if (botAi)
		return botAi->GetAiRegistry()->GetStrategyManager()->ContainsStrategy(STRATEGY_TYPE_TANK);

	switch (player->getClass()) 
	{
		case CLASS_DEATH_KNIGHT:
		case CLASS_PALADIN:
		case CLASS_WARRIOR:
			return true;
	}
	return false;
}

bool AiStatsManager::IsDps(Player* player)
{
	return !IsTank(player);
}

void AiStatsManager::Update()
{
}

int AiStatsManager::GetAttackerCount(float distance)
{
    return ai->GetMaster()->GetPlayerbotMgr()->GetGroupStatsManager()->GetAttackerCount();
}

float AiStatsManager::GetBalancePercent()
{
    return ai->GetMaster()->GetPlayerbotMgr()->GetGroupStatsManager()->GetBalancePercent();
}

map<Unit*, ThreatManager*>& AiStatsManager::GetAttackers() 
{
    return ai->GetMaster()->GetPlayerbotMgr()->GetGroupStatsManager()->GetAttackers();
}

