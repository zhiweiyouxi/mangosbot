#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

typedef pair<uint32, uint8> spellEffectPair;
typedef multimap<spellEffectPair, Aura*> AuraMap;

AiSpellManager::AiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
	lastSpellId = 0;
	lastSpellTarget = 0;
	lastCastTime = 0;
}


uint32 AiSpellManager::GetSpellId(const char* args) 
{
	string s = args;

	if (spellMap.find(s) != spellMap.end())
		return spellMap[s];

	uint32 id = FindSpellId(args);
	spellMap.insert(pair<string, uint32>(s, id));
	return id;
}

uint32 AiSpellManager::FindSpellId(const char* args) 
{
	if (!*args)
		return 0;

	string namepart = args;
	wstring wnamepart;

	if (!Utf8toWStr(namepart, wnamepart))
		return 0;

	wstrToLower(wnamepart);

	int loc = bot->GetSession()->GetSessionDbcLocale();

	uint32 foundSpellId = 0;
	bool foundExactMatch = false;
	bool foundMatchUsesNoReagents = false;

	for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr) {
		uint32 spellId = itr->first;

		if (itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled || IsPassiveSpell(spellId))
			continue;

		const SpellEntry* pSpellInfo = sSpellStore.LookupEntry(spellId);
		if (!pSpellInfo)
			continue;

		const string name = pSpellInfo->SpellName[loc];
		if (name.empty() || !Utf8FitTo(name, wnamepart))
			continue;

		bool isExactMatch = (name.length() == wnamepart.length()) ? true : false;
		bool usesNoReagents = (pSpellInfo->Reagent[0] <= 0) ? true : false;

		// if we already found a spell
		bool useThisSpell = true;
		if (foundSpellId > 0) {
			if (isExactMatch && !foundExactMatch) {}
			else if (usesNoReagents && !foundMatchUsesNoReagents) {}
			else if (spellId > foundSpellId && isExactMatch) {}
			else
				useThisSpell = false;
		}
		if (useThisSpell) {
			foundSpellId = spellId;
			foundExactMatch = isExactMatch;
			foundMatchUsesNoReagents = usesNoReagents;
		}
	}

	return foundSpellId;
}

bool AiSpellManager::HasAura(uint32 spellId, const Unit* player) 
{
	if (!spellId) 
		return false;

	for (AuraMap::const_iterator iter = player->GetAuras().begin(); iter != player->GetAuras().end(); ++iter) 
	{
		if (iter->second->GetId() == spellId)
			return true;
	}
	return false;
}

bool AiSpellManager::HasAnyAuraOf(Unit* player, ...)
{
	if (!player)
		return false;

	va_list vl;
	va_start(vl, player);

	const char* cur = NULL;
	do {
		cur = va_arg(vl, const char*);
		if (cur && HasAura(cur, player)) {
			va_end(vl);
			return true;
		}
	}
	while (cur);

	va_end(vl);
	return false;
}

bool AiSpellManager::CanCastSpell(uint32 spellid, Unit* target)
{
	if (!spellid)
		return false;

	if (!target)
		target = bot;

	if (!bot->HasSpell(spellid) || bot->HasSpellCooldown(spellid))
		return false;

	bool positiveSpell = IsPositiveSpell(spellid);
	if (positiveSpell && bot->IsHostileTo(target))
		return false;
	
	if (!positiveSpell && bot->IsFriendlyTo(target))
		return false;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
	if (!spellInfo)
		return false;

	uint64 oldSel = bot->GetSelection();
	bot->SetSelection(target->GetGUID());
	Spell *spell = new Spell(bot, spellInfo, false );
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    targets.setItemTarget(FindItemForSpell(spellInfo));
    spell->m_CastItem = FindItemForSpell(spellInfo);
	SpellCastResult result = spell->CheckCast(false);
	delete spell;
	bot->SetSelection(oldSel);

	switch (result)
	{
	case SPELL_FAILED_TOO_CLOSE:
	case SPELL_FAILED_NOT_BEHIND:
	case SPELL_FAILED_NOT_INFRONT:
	case SPELL_FAILED_NOT_STANDING:
	case SPELL_FAILED_UNIT_NOT_BEHIND:
	case SPELL_FAILED_UNIT_NOT_INFRONT:
	case SPELL_FAILED_OUT_OF_RANGE:
	case SPELL_FAILED_SUCCESS:
	case SPELL_FAILED_LINE_OF_SIGHT:
	case SPELL_FAILED_MOVING:
	case SPELL_FAILED_ONLY_STEALTHED:
	case SPELL_FAILED_ONLY_SHAPESHIFT:
	case SPELL_FAILED_SPELL_IN_PROGRESS:
	case SPELL_FAILED_TRY_AGAIN:
	case SPELL_FAILED_NOT_ON_STEALTHED:
	case SPELL_FAILED_NOT_ON_SHAPESHIFT:
	case SPELL_FAILED_NOT_IDLE:
	case SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW:
	case SPELL_FAILED_SUMMON_PENDING:
	case SPELL_FAILED_BAD_IMPLICIT_TARGETS:
	case SPELL_FAILED_BAD_TARGETS:
	case SPELL_CAST_OK:
    case SPELL_FAILED_ITEM_NOT_FOUND:
		return true;
	default:
		return false;
	}
}

bool AiSpellManager::IsSpellCastUseful(const char* name, Unit* target)
{
	uint32 spellid = GetSpellId(name);
	if (!spellid)
		return true; // there can be known alternatives

	if (!target)
		target = bot;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
	if (!spellInfo)
		return true; // there can be known alternatives

	if (spellInfo->AttributesEx2 & SPELL_ATTR_EX2_AUTOREPEAT_FLAG)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL);
		if (spell && spell->m_spellInfo->Id == spellid && spell->IsAutoRepeat())
			return false;
	}
	
	if (spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_2)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_MELEE_SPELL);
		if (spell && spell->m_spellInfo->Id == spellid && spell->IsNextMeleeSwingSpell())
			return false;
	}

    if (spellid == lastSpellId) 
    {
        Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
        if (pSpell)
            return false;
    }

    Item *item = FindItemForSpell(spellInfo);
    if (item && item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
        return false;

	return true;
}

Item* AiSpellManager::FindItemForSpell(const SpellEntry* const pSpellInfo) 
{
    for( uint8 slot=EQUIPMENT_SLOT_START; slot<EQUIPMENT_SLOT_END; slot++ ) {
        Item* const pItem = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, slot );
        if( !pItem )
            continue;

        if (pItem->IsFitToSpellRequirements(pSpellInfo))
            return pItem;
    }
    return NULL;
}

bool AiSpellManager::CastSpell(uint32 spellId, Unit* target)
{
	if (!target)
		target = bot;

    if (!bot->isInFrontInMap(target, 10))
    {
        bot->SetInFront(target);
		WorldPacket data;
		bot->BuildHeartBeatMsg( &data );
		bot->SendMessageToSet( &data, false );
		bot->SetPosition( bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetOrientation(), false );
    }

    lastSpellId = spellId;
    lastSpellTarget = target->GetGUID();
    lastCastTime = time(0);

	aiRegistry->GetMoveManager()->Stay();

    const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(lastSpellId);
    uint64 oldSel = bot->GetSelection();
    bot->SetSelection(lastSpellTarget);
    
    Spell *spell = new Spell(bot, pSpellInfo, false);
    SpellCastTargets targets;
    targets.setUnitTarget(target);
    targets.setItemTarget(FindItemForSpell(pSpellInfo));
    spell->prepare(&targets, false);
    
    bot->SetSelection(oldSel);

    uint32 castTime = GetSpellCastTime(pSpellInfo) / 1000;

	if (pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_1 ||
		pSpellInfo->AttributesEx & SPELL_ATTR_EX_CHANNELED_2)
		castTime += GetSpellDuration(pSpellInfo) / 1000;

    uint32 globalCooldown = CalculateGlobalCooldown(spellId);
    if (castTime < globalCooldown)
        castTime = globalCooldown;

    ai->SetNextCheckDelay(castTime);
    return true;
}

void AiSpellManager::FinishSpell()
{
    Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
    if (!pSpell)
        return;

    if (pSpell->IsChannelActive())
		ai->SetNextCheckDelay(GetSpellDuration(pSpell->m_spellInfo) / 1000);
}

void AiSpellManager::InterruptSpell()
{
	WorldPacket* const packet = new WorldPacket(CMSG_CANCEL_CAST, 5);
	*packet << lastSpellId;
	*packet << lastSpellTarget;
	bot->GetSession()->QueuePacket(packet);

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_MAX_SPELL; type++)
        bot->InterruptSpell((CurrentSpellTypes)type);

	SpellInterrupted(lastSpellId);
}

void AiSpellManager::SpellInterrupted(uint32 spellid)
{
    if (lastSpellId != spellid)
        return;

	int castTimeSpent = time(0) - lastCastTime;
	
	int32 globalCooldown = CalculateGlobalCooldown(lastSpellId);
	if (castTimeSpent < globalCooldown)
		ai->SetNextCheckDelay(globalCooldown - castTimeSpent);
	else
		ai->SetNextCheckDelay(0);

	lastSpellId = 0;
	lastSpellTarget = 0;
	lastCastTime = 0;
}

int32 AiSpellManager::CalculateGlobalCooldown(uint32 spellid)
{
	if (!spellid) 
		return 0;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );

	if (!spellInfo || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 || 
		spellInfo->Attributes & SPELL_ATTR_ON_NEXT_SWING_2 || 
		spellInfo->Attributes & SPELL_ATTR_OUTDOORS_ONLY ||
		spellInfo->Attributes & SPELL_ATTR_DISABLED_WHILE_ACTIVE)
		return 0;

    if (spellInfo->AttributesEx3 & SPELL_ATTR_EX3_REQ_WAND)
        return GLOBAL_COOLDOWN;
	
	return GLOBAL_COOLDOWN;
}

void AiSpellManager::RemoveAura(const char* name)
{
	uint32 spellid = GetSpellId(name);
	if (spellid && HasAura(spellid, bot))
		bot->RemoveAurasDueToSpell(spellid);
}

bool AiSpellManager::IsSpellCasting(Unit* player)
{
	return player->IsNonMeleeSpellCasted(true);
}

bool AiSpellManager::HasAuraToDispel(Unit* player, uint32 dispelType) 
{
	Unit::AuraMap &uAuras = player->GetAuras();
	for (Unit::AuraMap::const_iterator itr = uAuras.begin(); itr != uAuras.end(); ++itr)
	{
		const SpellEntry* entry = itr->second->GetSpellProto();
		uint32 spellId = entry->Id;
		if (IsPositiveSpell(spellId))
			continue;

		if (canDispel(entry, dispelType))
			return TRUE;
	}
	return FALSE;
}


bool AiSpellManager::canDispel(const SpellEntry* entry, uint32 dispelType) 
{
	if (entry->Dispel == dispelType) {
		return !entry->SpellName[0] ||
			(strcmpi((const char*)entry->SpellName[0], "demon skin") &&
			strcmpi((const char*)entry->SpellName[0], "mage armor") &&
			strcmpi((const char*)entry->SpellName[0], "frost armor") &&
			strcmpi((const char*)entry->SpellName[0], "ice armor"));
	}
	return false;
}

void AiSpellManager::ListSpells()
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbcLocale();

	std::ostringstream posOut;
	std::ostringstream negOut;

	const std::string ignoreList = ",Opening,Closing,Stuck,Remove Insignia,Opening - No Text,Grovel,Duel,Honorless Target,";
	std::string alreadySeenList = ",";

	for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr) {
		const uint32 spellId = itr->first;

		if (itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled || IsPassiveSpell(spellId))
			continue;

		const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
		if (!pSpellInfo)
			continue;

		//|| name.find("Teleport") != -1

		std::string comp = ",";
		comp.append(pSpellInfo->SpellName[loc]);
		comp.append(",");

		if (!(ignoreList.find(comp) == std::string::npos && alreadySeenList.find(comp) == std::string::npos))
			continue;

		alreadySeenList += pSpellInfo->SpellName[loc];
		alreadySeenList += ",";

		if (IsPositiveSpell(spellId))
			posOut << " |cffffffff|Hspell:" << spellId << "|h["
			<< pSpellInfo->SpellName[loc] << "]|h|r";
		else
			negOut << " |cffffffff|Hspell:" << spellId << "|h["
			<< pSpellInfo->SpellName[loc] << "]|h|r";
	}

	aiRegistry->GetSocialManager()->TellMaster("here's my non-attack spells:");
	aiRegistry->GetSocialManager()->TellMaster(posOut.str().c_str());
	
	aiRegistry->GetSocialManager()->TellMaster("here's my attack spells:");
	aiRegistry->GetSocialManager()->TellMaster(negOut.str().c_str());
}

void AiSpellManager::Mount(int32 master_speed1, int32 master_speed2)
{
	uint32 spellMount = 0;
	for(PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
	{
		uint32 spellId = itr->first;
		if(itr->second->state == PLAYERSPELL_REMOVED || itr->second->disabled || IsPassiveSpell(spellId))
			continue;
		const SpellEntry* pSpellInfo = sSpellStore.LookupEntry(spellId);
		if (!pSpellInfo)
			continue;

		if(pSpellInfo->EffectApplyAuraName[0] == SPELL_AURA_MOUNTED)
		{
			if(pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
			{
				if(pSpellInfo->EffectBasePoints[1] == master_speed1 && CanCastSpell(spellId, bot))
				{
					spellMount = spellId;
					break;
				}
			}
			else if((pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
				&& (pSpellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED))
			{
				if((pSpellInfo->EffectBasePoints[1] == master_speed1)
					&& (pSpellInfo->EffectBasePoints[2] == master_speed2) && CanCastSpell(spellId, bot))
				{
					spellMount = spellId;
					break;
				}
			}
			else if((pSpellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
				&& (pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED))
			{
				if((pSpellInfo->EffectBasePoints[2] == master_speed2) 
					&& (pSpellInfo->EffectBasePoints[1] == master_speed1) && CanCastSpell(spellId, bot))
				{
					spellMount = spellId;
					break;
				}
			}
		}
	}

	if(spellMount > 0) CastSpell(spellMount, bot);
}

void AiSpellManager::Unmount()
{
	WorldPacket emptyPacket;
	bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
}

void AiSpellManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "spells")
	{
		ListSpells();
	}
}

void AiSpellManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
	case SMSG_SPELL_FAILURE:
		{
			WorldPacket p(packet);
			uint64 casterGuid = extractGuid(p);
			if (casterGuid != bot->GetGUID())
				return;
			uint8  castCount;
			uint32 spellId;
			p >> castCount;
			p >> spellId;
			SpellInterrupted(spellId);
			return;
		}

	case SMSG_SPELL_GO:
		{
			WorldPacket p(packet);
			uint64 casterGuid = extractGuid(p);
			if (casterGuid != bot->GetGUID())
				return;
			FinishSpell();
			return;
		}
    case SMSG_SPELL_DELAYED:
        {
            WorldPacket p(packet);
            uint64 casterGuid = extractGuid(p);
            if (casterGuid != bot->GetGUID())
                return;
            bot->GetPlayerbotAI()->IncreaseNextCheckDelay(1);
        }
    }
}
