#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiStatsManager : public AiStatsManager
    {
    public:
        MockAiStatsManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiStatsManager(ai, aiRegistry) 
        {
			health[MockedTargets::GetCurrentTarget()] = 100.0f;
			health[MockedTargets::GetPartyMember()] = 100.0f;
			health[MockedTargets::GetPet()] = 100.0f;
			health[MockedTargets::GetSelf()] = 100.0f;
        
			mana[MockedTargets::GetCurrentTarget()] = 100.0f;
			mana[MockedTargets::GetPartyMember()] = 100.0f;
			mana[MockedTargets::GetPet()] = 100.0f;
			mana[MockedTargets::GetSelf()] = 100.0f;
		
			aggro = TRUE; 
			attackerCount = 1;myAttackerCount = 1;
			balancePercent = 100;
		}

	public:
		virtual uint8 GetHealthPercent(Unit* target);
		virtual uint8 GetRage(Unit* target);
		virtual uint8 GetEnergy(Unit* target);
		virtual uint8 GetManaPercent(Unit* target);
		virtual bool HasMana(Unit* target);
		virtual bool IsDead(Unit* target);
		virtual uint8 GetComboPoints(Player* target);
		virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE) { return attackerCount; }
		virtual int GetMyAttackerCount() {return myAttackerCount; }
		virtual float GetBalancePercent() { return balancePercent; }
		virtual bool HasAggro(Unit* target) { return aggro; }
		virtual bool IsMounted() { return false; }

		map<Unit*, uint8> health;
		map<Unit*, uint8> rage;
		map<Unit*, uint8> energy;
		map<Unit*, uint8> mana;
		map<Player*, uint8> comboPoints;
    
		bool aggro;
		int attackerCount;
		int myAttackerCount;
		float balancePercent;
	};

}