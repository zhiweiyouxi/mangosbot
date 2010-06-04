#pragma once

class Player;

using namespace std;

namespace ai 
{
	class AiGroupStatsManager 
	{
	public:
		AiGroupStatsManager(Player* master)
		{
            this->master = master;
            balancePercent = 100;
		}

    public:
        virtual void Update();
		virtual int GetAttackerCount(float distance = 50);
        virtual float GetBalancePercent() { return balancePercent; }

	public:
        virtual map<Unit*, ThreatManager*>& GetAttackers() { return attackers; }

	private:
        void findAllAttackers(map<Unit*, ThreatManager*> &out);
		void findAllAttackers(Player *player, map<Unit*, ThreatManager*> &out);
        float CalculateBalancePercent();

    private:
        Player* master;
        map<Unit*, ThreatManager*> attackers;
        float balancePercent;

	};

};