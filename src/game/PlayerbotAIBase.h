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
	
class PlayerbotAIBase
{
public:
	PlayerbotAIBase();

public:
	bool CanUpdateAI();
	void SetNextCheckDelay(const uint32 delay);
	void YieldThread();

protected:
	time_t nextAICheckTime;
};
