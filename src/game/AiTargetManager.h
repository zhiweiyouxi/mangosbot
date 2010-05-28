#pragma once

#include "Player.h"
#include "PlayerbotAI.h"
#include "AiManagerBase.h"
#include "AiSpellManager.h"
#include "DBCStructure.h"
#include "AiStatsManager.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;
	class AiTargetManager;

	typedef bool (AiTargetManager::*FindPlayerPredicate)(Unit*, void*);
	typedef bool (AiTargetManager::*SpellEntryPredicate)(SpellEntry const*);


	class FindTargetStrategy
	{
	public:
		FindTargetStrategy() 
		{
			result = NULL;
		}

	public:
		void CheckAttackers(Player* player);
		Unit* GetResult() { return result; }

	protected:
		virtual void CheckAttacker(Player* player, ThreatManager* threatManager) = NULL;
		void GetPlayerCount(Player* player, Unit* creature, int* tankCount, int* dpsCount);

	protected:
		Unit* result;
	};

	class FindTargetForTankStrategy : public FindTargetStrategy
	{
	public:
		FindTargetForTankStrategy() : FindTargetStrategy()
		{
			minThreat = 0;
			minTankCount = 0;
			maxDpsCount = 0;
		}

	protected:
		virtual void CheckAttacker(Player* player, ThreatManager* threatManager);

	protected:
		float minThreat;
		int minTankCount;
		int maxDpsCount;
	};

	class FindTargetForDpsStrategy : public FindTargetStrategy
	{
	public:
		FindTargetForDpsStrategy() : FindTargetStrategy()
		{
			minThreat = 0;
			maxTankCount = 0;
			minDpsCount = 0;
		}

	protected:
		virtual void CheckAttacker(Player* player, ThreatManager* threatManager);

	protected:
		float minThreat;
		int maxTankCount;
		int minDpsCount;
	};

	class AiTargetManager : public AiManagerBase
	{
	public:
		AiTargetManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual Unit* GetPartyMemberWithoutAura(const char* spell);
		virtual Unit* GetPartyMinHealthPlayer();
		virtual Unit* GetDeadPartyMember();
		virtual Unit* GetPartyMemberToDispell(uint32 dispelType);
		virtual Unit* FindTargetForTank();
		virtual Unit* FindTargetForDps();
		virtual Unit* GetCurrentTarget();
		virtual Player* GetSelf();
		virtual Unit* GetPet();
		virtual Player* GetMaster();

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

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
		bool CanHealPet(Pet* pet);

	private:
		Unit* FindTarget(FindTargetStrategy* strategy);

	private:
		bool PlayerWithoutAuraPredicate(Unit* player, void *param /*const char* spell*/);

	};

};