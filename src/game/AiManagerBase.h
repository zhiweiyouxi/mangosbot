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
	}

protected:
	PlayerbotAIBase* ai;
	Player* bot;
};

};