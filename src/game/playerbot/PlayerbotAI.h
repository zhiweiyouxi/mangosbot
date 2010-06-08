#pragma once

#include "PlayerbotAIBase.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;

namespace ai 
{
	class AiManagerRegistry;

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
};

class PlayerbotAI : public PlayerbotAIBase
{
public:
	PlayerbotAI();
	PlayerbotAI(PlayerbotMgr* mgr, Player* bot);
	virtual ~PlayerbotAI();

public:
	void UpdateAI(uint32 elapsed);
	void HandleCommand(const string& text, Player& fromPlayer);
	void HandleBotOutgoingPacket(const WorldPacket& packet);
    void HandleMasterIncomingPacket(const WorldPacket& packet);
	void HandleTeleportAck();

public:
	Player* GetBot() { return bot; }
	Player* GetMaster() { return mgr->GetMaster(); }
	ai::AiManagerRegistry* GetAiRegistry() { return aiRegistry; }
    ai::AiGroupStatsManager* GetGroupStatsManager() { return mgr->GetGroupStatsManager(); }

protected:
	Player* bot;
	PlayerbotMgr* mgr;
	ai::AiManagerRegistry* aiRegistry;
};

