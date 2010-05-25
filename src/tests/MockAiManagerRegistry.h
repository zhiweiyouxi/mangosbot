#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiStatsManager.h"
#include "AiManagerRegistry.h"

namespace ai
{
    class MockAiManagerRegistry : public AiManagerRegistry
    {
    public:
		MockAiManagerRegistry(PlayerbotAIBase* ai, std::string *buffer);
		virtual ~MockAiManagerRegistry();
	};

}