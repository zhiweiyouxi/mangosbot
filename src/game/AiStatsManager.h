#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"

using namespace std;

namespace ai 
{
	class AiStatsManager : public AiManagerBase
	{
	public:
		AiStatsManager(PlayerbotAIBase* ai) : AiManagerBase(ai)
		{
		}

	public:
		virtual uint8 GetHealthPercent(Unit* target);
	};

};