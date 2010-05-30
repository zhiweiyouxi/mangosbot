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

	class FindTargetStrategy
	{
	public:
		FindTargetStrategy(AiManagerRegistry* aiRegistry)
		{
			result = NULL;
			this->aiRegistry = aiRegistry;
		}

	public:
		void CheckAttackers(Player* bot, Player* player);
		Unit* GetResult() { return result; }

	protected:
		virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager) = NULL;
		void GetPlayerCount(Player* bot, Unit* creature, int* tankCount, int* dpsCount);

	protected:
		Unit* result;
		AiManagerRegistry* aiRegistry;

    protected:
        map<Unit*, int> tankCountCache;
        map<Unit*, int> dpsCountCache;
        set<Unit*> alreadyChecked;
	};

	class FindTargetForTankStrategy : public FindTargetStrategy
	{
	public:
		FindTargetForTankStrategy(AiManagerRegistry* aiRegistry) : FindTargetStrategy(aiRegistry)
		{
			minThreat = 0;
			minTankCount = 0;
			maxDpsCount = 0;
		}

	protected:
		virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager);

	protected:
		float minThreat;
		int minTankCount;
		int maxDpsCount;
	};

	class FindTargetForDpsStrategy : public FindTargetStrategy
	{
	public:
		FindTargetForDpsStrategy(AiManagerRegistry* aiRegistry) : FindTargetStrategy(aiRegistry)
		{
			minThreat = 0;
			maxTankCount = 0;
			minDpsCount = 0;
		}

	protected:
		virtual void CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager);

	protected:
		float minThreat;
		int maxTankCount;
		int minDpsCount;
	};

};