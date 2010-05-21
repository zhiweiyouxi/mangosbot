#include "pchdef.h"
#include "AiTargetManager.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"

using namespace ai;
using namespace std;

Unit* AiTargetManager::GetPartyMemberWithoutAura(const char* spell) 
{
	return FindPartyMember(&AiTargetManager::PlayerWithoutAuraPredicate, (void*)spell); 
}

Unit* AiTargetManager::GetPartyMinHealthPlayer()
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	MinValueCalculator calc(100);
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (!CheckPredicate(player, NULL, NULL) || !player->isAlive())
			continue;

		uint8 health = statsManager->GetHealthPercent(player);
		if (health < 25 || !IsTargetOfHealingSpell(player))
			calc.probe(health, player);

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet)) 
		{
			health = statsManager->GetHealthPercent(pet);
			if (health < 25 || !IsTargetOfHealingSpell(player))
				calc.probe(health, player);
		}
	}
	return (Unit*)calc.param;
}

Unit* AiTargetManager::GetDeadPartyMember() 
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (CheckPredicate(player, NULL, NULL) && !player->isAlive() && !IsTargetOfResurrectSpell(player))
			return player;
	}
	return NULL;
}

Unit* AiTargetManager::FindPartyMember(FindPlayerPredicate predicate, void* param)
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (CheckPredicate(player, predicate, param))
			return player;

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet) && CheckPredicate(player, predicate, param))
			return player;
	}
	return NULL;
}

bool AiTargetManager::CheckPredicate(Unit* player, FindPlayerPredicate predicate, void *param) 
{
	return (player != bot && 
		bot->GetDistance(player) < 50.0f &&
		bot->IsWithinLOS(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ()) &&
		(predicate==NULL || (this->*predicate)(player, param)));
}

bool AiTargetManager::PlayerWithoutAuraPredicate(Unit* player, void *param )
{
	return player->isAlive() && !spellManager->HasAura((const char*)param, player);
}


bool AiTargetManager::IsHealingSpell(SpellEntry const* spell) {
	for (int i=0; i<3; i++) {
		if (spell->Effect[i] == SPELL_EFFECT_HEAL ||
			spell->Effect[i] == SPELL_EFFECT_HEAL_MAX_HEALTH ||
			spell->Effect[i] == SPELL_EFFECT_HEAL_MECHANICAL || 
			spell->Effect[i] == SPELL_EFFECT_HEAL_PCT)
			return true;
	}
	return false;
}

bool AiTargetManager::IsResurrectSpell(SpellEntry const* spell) {
	for (int i=0; i<3; i++) {
		if (spell->Effect[i] == SPELL_EFFECT_RESURRECT || 
			spell->Effect[i] == SPELL_EFFECT_RESURRECT_NEW || 
			spell->Effect[i] == SPELL_EFFECT_SELF_RESURRECT)
			return true;
	}
	return false;
}


bool AiTargetManager::IsTargetOfHealingSpell(Player* target) {
	return IsTargetOfSpellCast(target, &AiTargetManager::IsHealingSpell);
}

bool AiTargetManager::IsTargetOfResurrectSpell(Player* target) {
	return IsTargetOfSpellCast(target, &AiTargetManager::IsResurrectSpell);
}

bool AiTargetManager::IsTargetOfSpellCast(Player* target, SpellEntryPredicate predicate) 
{
	Group* group = bot->GetGroup();
	uint32 targetGuid = target ? target->GetGUID() : bot->GetGUID();

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if (player == bot)
			continue;

		if (player->IsNonMeleeSpellCasted(true)) 
		{
			for (int type = CURRENT_GENERIC_SPELL; type < CURRENT_MAX_SPELL; type++) {
				Spell* spell = player->GetCurrentSpell((CurrentSpellTypes)type);
				if (spell && (this->*predicate)(spell->m_spellInfo) && 
					(spell->CheckTarget(target, 0) ||
					spell->CheckTarget(target, 1) ||
					spell->CheckTarget(target, 2)))
					return true;
			}
		}
	}

	return false;
}

Unit* AiTargetManager::GetPartyMemberToDispell(uint32 dispelType)
{
	Group* group = bot->GetGroup();
	if (!group)
		return NULL;
	
	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* player = gref->getSource();
		if( !player || !player->isAlive() || player == bot)
			continue;

		if (HasAuraToDispel(player, dispelType))
			return player;

		Pet* pet = player->GetPet();
		if (pet && CanHealPet(pet) && HasAuraToDispel(pet, dispelType))
			return pet;
	}

	return NULL;
}


bool AiTargetManager::HasAuraToDispel(Unit* player, uint32 dispelType) 
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

bool AiTargetManager::canDispel(const SpellEntry* entry, uint32 dispelType) {
	if (entry->Dispel == dispelType) {
		return !entry->SpellName[0] ||
			(strcmpi((const char*)entry->SpellName[0], "demon skin") &&
			strcmpi((const char*)entry->SpellName[0], "mage armor") &&
			strcmpi((const char*)entry->SpellName[0], "frost armor") &&
			strcmpi((const char*)entry->SpellName[0], "ice armor"));
	}
	return false;
}


void AiTargetManager::findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out)
{
	while( ref )
	{
		ThreatManager *source = ref->getSource();
		Unit *attacker = source->getOwner();
		if (attacker && 
			!attacker->isDead() && 
			!attacker->IsPolymorphed() && 
			!attacker->isFrozen() && 
			!attacker->IsFriendlyTo(bot) && 
			bot->IsWithinLOSInMap(attacker))
		{
			bool found = FALSE;
			for (std::list<ThreatManager*>::iterator i = out.begin(); i != out.end(); i++)
			{
				ThreatManager *cur = *i;
				if (cur->getOwner() == attacker)
				{
					found = TRUE;
					break;
				}
			}
			if (!found)
				out.push_back(source);
		}
		ref = ref->next();
	}
}

void AiTargetManager::findAllAttackers(std::list<ThreatManager*> &out)
{
	if (bot->GetGroup())
	{
		GroupReference *gref = bot->GetGroup()->GetFirstMember();
		while( gref )
		{
			HostileReference *ref = gref->getSource()->getHostileRefManager().getFirst();
			findAllAttackers(ref, out);
			gref = gref->next();
		}
	}
}

Unit* AiTargetManager::FindLeastThreat()
{
	std::list<ThreatManager*> attackers;
	findAllAttackers(attackers);

	float minThreat = 1e8;
	Unit* target = NULL;
	for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
	{  
		ThreatManager* attacker = *i;
		float threat = attacker->getThreat(bot);
		if (!target || threat < minThreat)
		{
			minThreat = threat;
			target = attacker->getOwner();
		}
	}
	return target;
}

Unit* AiTargetManager::FindBiggerThreat()
{
	std::list<ThreatManager*> attackers;
	findAllAttackers(attackers);

	float maxThreat = -1;
	Unit* target = NULL;
	for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
	{  
		ThreatManager* attacker = *i;
		float threat = attacker->getThreat(bot);
		if (!target || threat > maxThreat)
		{
			maxThreat = threat;
			target = attacker->getOwner();
		}
	}
	return target;
}

Unit* AiTargetManager::GetCurrentTarget()
{
	uint64 guid = bot->GetSelection();
	return guid ? ObjectAccessor::GetUnit(*bot, guid) : NULL;
}

Player* AiTargetManager::GetSelf()
{
	return bot;
}

Player* AiTargetManager::GetMaster()
{
	return ai->GetMaster();
}

Unit* AiTargetManager::GetPet()
{
	return bot->GetPet();
}

bool AiTargetManager::CanHealPet(Pet* pet) 
{
	PetType type = pet->getPetType();
	return type != SUMMON_PET && type != MINI_PET;
}
