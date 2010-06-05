#pragma once

class Player;
#include "LazyCalculatedValue.h"

using namespace std;

namespace ai 
{
	class AiGroupStatsManager 
	{
	public:
		AiGroupStatsManager(Player* master);
        virtual ~AiGroupStatsManager();

    public:
        virtual void Update();
		virtual int GetAttackerCount(float distance = 50);
        virtual float GetBalancePercent() { return balancePercent->GetValue(); }

	public:
        virtual map<Unit*, ThreatManager*> GetAttackers() { return attackers->GetValue(); }

	private:
        map<Unit*, ThreatManager*> findAllAttackers();
		void findAllAttackers(Player *player, map<Unit*, ThreatManager*> &out);
        float CalculateBalancePercent();

    private:
        Player* master;
        
        LazyCalculatedValue<map<Unit*, ThreatManager*>, AiGroupStatsManager> *attackers;

        LazyCalculatedValue<float, AiGroupStatsManager> *balancePercent;
	};

};