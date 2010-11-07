#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
	class MockPlayerbotAIBase : public PlayerbotAI
	{
	public:
		MockPlayerbotAIBase() : PlayerbotAI() {}
	};

    class MockAiManagerRegistry : public AiManagerRegistry
    {
    public:
		MockAiManagerRegistry();
		virtual ~MockAiManagerRegistry();

	public:
		std::string buffer;
		MockPlayerbotAIBase ai;
	};

}