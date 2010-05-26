#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiManagerRegistry.h"

namespace ai
{
	class MockPlayerbotAIBase : public PlayerbotAIBase
	{
	public:
		MockPlayerbotAIBase() : PlayerbotAIBase(NULL, NULL) {}
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