#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "AiSpellManager.h"
#include "DBCStructure.h"
#include "AiStatsManager.h"

using namespace std;

namespace ai 
{
	class AiTargetManager;

	typedef bool (AiTargetManager::*FindPlayerPredicate)(Unit*, void*);
	typedef bool (AiTargetManager::*SpellEntryPredicate)(SpellEntry const*);

	class AiTargetManager : public AiManagerBase
	{
	public:
		AiTargetManager(PlayerbotAIBase* ai, AiSpellManager* spellManager, AiStatsManager* statsManager) : AiManagerBase(ai)
		{
			this->spellManager = spellManager;
			this->statsManager = statsManager;
		}

	public:
		virtual Unit* GetPartyMemberWithoutAura(const char* spell);
		virtual Unit* GetPartyMinHealthPlayer();
		virtual Unit* GetDeadPartyMember();
		virtual Unit* GetPartyMemberToDispell(uint32 dispelType);

	private:
		Unit* FindPartyMember(FindPlayerPredicate predicate, void *param);
		bool CheckPredicate(Unit* player, FindPlayerPredicate predicate, void *param);
		bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate predicate);
		bool IsTargetOfHealingSpell(Player* target);
		bool IsTargetOfResurrectSpell(Player* target);
		virtual bool HasAuraToDispel(uint32 dispelType) { return HasAuraToDispel(bot, dispelType); }
		bool HasAuraToDispel(Unit* player, uint32 dispelType);
		bool canDispel(const SpellEntry* entry, uint32 dispelType);

	private:
		bool IsHealingSpell(SpellEntry const* spell);
		bool IsResurrectSpell(SpellEntry const* spell);

	private:
		bool PlayerWithoutAuraPredicate(Unit* player, void *param /*const char* spell*/);

	private:
		AiSpellManager* spellManager;
		AiStatsManager* statsManager;
	};

};