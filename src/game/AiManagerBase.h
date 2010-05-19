#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"

using namespace std;

namespace ai 
{

class AiManagerBase
{
public:
	AiManagerBase(PlayerbotAIBase* ai) 
	{
		this->ai = ai;
		this->bot = ai->GetBot();
		this->master = ai->GetMaster();
	}

protected:
	PlayerbotAIBase* ai;
	Player* bot;
	Player* master;
};

};