#pragma once

#include "Player.h"
#include "PlayerbotMgr.h"

using namespace std;

#define GLOBAL_COOLDOWN 2

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f


namespace ai
{

	class MinValueCalculator {
	public:
		MinValueCalculator(float def = 0.0f) {
			param = NULL;
			minValue = def;
		}

	public:
		void probe(float value, void* p) {
			if (!param || minValue >= value) {
				minValue = value;
				param = p;
			}
		}

	public:
		void* param;
		float minValue;
	};

	class PlayerbotAIBase 
	{
	public:
		PlayerbotAIBase(PlayerbotMgr* const mgr, Player* const bot) 
		{
			this->mgr = mgr;
			this->bot = bot;
			nextAICheckTime = 0;
		}

	public:
		bool CanUpdateAI();
		void SetNextCheckDelay(const uint32 delay);

	public:
		Player* GetBot() { return bot; }
		Player* GetMaster() { return mgr->GetMaster(); }

	protected:
		Player* bot;
		PlayerbotMgr* mgr;
		time_t nextAICheckTime;
	};

};