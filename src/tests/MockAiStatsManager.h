#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiStatsManager.h"

namespace ai
{
    class MockAiStatsManager : public AiStatsManager
    {
    public:
        MockAiStatsManager(PlayerbotAIBase* ai) : AiStatsManager(ai) 
        {
			health[MockedTargets::GetCurrentTarget()] = 100.0f;
			health[MockedTargets::GetPartyMember()] = 100.0f;
			health[MockedTargets::GetPet()] = 100.0f;
			health[MockedTargets::GetSelf()] = 100.0f;
        }

	public:
		virtual uint8 GetHealthPercent(Unit* target);

		map<Unit*, uint8> health;
    };

}