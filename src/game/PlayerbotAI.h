#pragma once

#define GLOBAL_COOLDOWN 2
#define BOT_REACT_DELAY 1

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f

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

class PlayerbotAI 
{
public:
	// only for testing
	PlayerbotAI();
	PlayerbotAI(PlayerbotMgr* mgr, Player* bot);
	virtual ~PlayerbotAI();

public:
	// This is called from Unit.cpp and is called every second (I think)
	void UpdateAI(uint32 elapsed);

	// This is called from ChatHandler.cpp when there is an incoming message to the bot
	// from a whisper or from the party channel
	void HandleCommand(const string& text, Player& fromPlayer);

	// This is called by WorldSession.cpp
	// It provides a view of packets normally sent to the client.
	// Since there is no client at the other end, the packets are dropped of course.
	// For a list of opcodes that can be caught see Opcodes.cpp (SMSG_* opcodes only)
	void HandleBotOutgoingPacket(const WorldPacket& packet);

	// This is called by WorldSession.cpp
	// when it detects that a bot is being teleported. It acknowledges to the server to complete the
	// teleportation
	void HandleTeleportAck();

	bool CanUpdateAI();
	void SetNextCheckDelay(const uint32 delay);
	void YieldThread();

public:
	Player* GetBot() { return bot; }
	Player* GetMaster() { return mgr->GetMaster(); }
	ai::AiManagerRegistry* GetAiRegistry() { return aiRegistry; }

protected:
	Player* bot;
	PlayerbotMgr* mgr;
	time_t nextAICheckTime;
	ai::AiManagerRegistry* aiRegistry;
};

