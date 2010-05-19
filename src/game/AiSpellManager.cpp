#include "pchdef.h"
#include "AiSpellManager.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "Unit.h"
#include "Player.h"
#include "WorldSession.h"
#include "WorldPacket.h"

using namespace ai;
using namespace std;

typedef pair<uint32, uint8> spellEffectPair;
typedef multimap<spellEffectPair, Aura*> AuraMap;

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

bool AiSpellManager::CanCastSpell(uint32 spellid, Unit* target)
{
	if (!spellid)
		return false;

	if (!target)
		target = bot;

	if (!bot->HasSpell(spellid) || bot->HasSpellCooldown(spellid))
		return false;

	if (IsPositiveSpell(spellid) && bot->IsHostileTo(target))
		return false;
	else if (bot->IsFriendlyTo(target))
		return false;

	SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
	if (!spellInfo)
		return false;

	if (target->IsImmunedToSpell(spellInfo))
		return false;

	Spell *spell = new Spell(bot, spellInfo, false );
	bool res = (spell->CheckPower() == SPELL_CAST_OK);
	delete spell;

	return res;
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

	const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
    bot->CastSpell(target, pSpellInfo, false);

    Spell* const pSpell = bot->FindCurrentSpellBySpellId(spellId);
    if (!pSpell)
        return false;

    lastSpellId = spellId;
	lastSpellTarget = target->GetGUID();

	int32 castTime = (int32)ceil((float)pSpell->GetCastTime()/1000.0f);

	if (pSpell->IsChannelActive() || pSpell->IsAutoRepeat())
		castTime += (GetSpellDuration(pSpell->m_spellInfo) / 1000);
	else if (pSpell->IsAutoRepeat())
		return castTime += 6;

	if (castTime < GLOBAL_COOLDOWN) 
		castTime = GLOBAL_COOLDOWN;

	lastCastTime = time(0);
	ai->SetNextCheckDelay(castTime);
    return true;
}

void AiSpellManager::InterruptSpell()
{
	WorldPacket* const packet = new WorldPacket(CMSG_CANCEL_CAST, 5);
	*packet << lastSpellId;
	*packet << lastSpellTarget;
	bot->GetSession()->QueuePacket(packet);

	int castTimeSpent = time(0) - lastCastTime;
	if (castTimeSpent < GLOBAL_COOLDOWN)
		ai->SetNextCheckDelay(GLOBAL_COOLDOWN - castTimeSpent);

	lastSpellId = 0;
	lastSpellTarget = 0;
	lastCastTime = 0;
}

void AiSpellManager::RemoveAura(const char* name)
{
	uint32 spellid = GetSpellId(name);
	if (spellid)
		bot->RemoveAurasDueToSpell(spellid);
}