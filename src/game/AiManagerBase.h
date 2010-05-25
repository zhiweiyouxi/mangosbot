#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;

	class AiManagerBase
	{
	public:
		AiManagerBase(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry) 
		{
			this->ai = ai;
			this->bot = ai->GetBot();
			this->aiRegistry = aiRegistry;
		}

	protected:
		PlayerbotAIBase* ai;
		Player* bot;
		AiManagerRegistry* aiRegistry;
	};

};