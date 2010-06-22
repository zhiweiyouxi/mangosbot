#pragma once

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
    void IncreaseNextCheckDelay(uint32 delay);
	void YieldThread();

protected:
	time_t nextAICheckTime;
};
