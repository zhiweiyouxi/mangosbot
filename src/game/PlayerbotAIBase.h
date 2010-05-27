#pragma once

#include "Player.h"
#include "PlayerbotMgr.h"
#include "Chat.h"

using namespace std;

#define GLOBAL_COOLDOWN 2
#define BOT_REACT_DELAY 1

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f

class PlayerbotChatHandler: protected ChatHandler
{
public:
	explicit PlayerbotChatHandler(Player* pMasterPlayer) : ChatHandler(pMasterPlayer) {}
	bool revive(const Player& botPlayer) { return HandleReviveCommand(botPlayer.GetName()); }
	bool teleport(const Player& botPlayer) { return HandleNamegoCommand(botPlayer.GetName()); }
	void sysmessage(const char *str) { SendSysMessage(str); }
	bool dropQuest(const char *str) { return HandleQuestRemove(str); }
};

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
		PlayerbotAIBase(PlayerbotMgr* mgr, Player* bot) 
		{
			this->mgr = mgr;
			this->bot = bot;
			nextAICheckTime = 0;
		}

	public:
		bool CanUpdateAI();
		void SetNextCheckDelay(const uint32 delay);
		void YieldThread();

	public:
		Player* GetBot() { return bot; }
		Player* GetMaster() { return mgr->GetMaster(); }

	protected:
		Player* bot;
		PlayerbotMgr* mgr;
		time_t nextAICheckTime;
	};

};