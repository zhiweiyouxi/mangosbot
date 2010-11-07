#pragma once

class Player;
#include "AttackerMapProvider.h"
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
        virtual float GetBalancePercent() { return balancePercent->GetValue(); }

	public:
        virtual int GetAttackerCount(float distance = 50){ return attackerMapProvider->GetAttackers().size(); }
        virtual AttackerMap GetAttackers() { return attackerMapProvider->GetAttackers(); }

	private:
        float CalculateBalancePercent();

    private:
        Player* master;
        AttackerMapProvider* attackerMapProvider;
        LazyCalculatedValue<float, AiGroupStatsManager> *balancePercent;
	};

};