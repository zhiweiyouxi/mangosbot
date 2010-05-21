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
		virtual uint8 GetRage(Unit* target);
		virtual uint8 GetEnergy(Unit* target);
		virtual uint8 GetManaPercent(Unit* target);
		virtual uint8 GetComboPoints(Player* target);
		virtual bool HasMana(Unit* target);
		virtual bool IsDead(Unit* target);
	};

};