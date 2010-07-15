#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiStrategyManager : public AiStrategyManager
    {
    public:
        MockAiStrategyManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiStrategyManager(ai, aiRegistry) 
        {
            this->buffer = buffer;
		}

	public:
        virtual void ChangeCombatStrategy(const char* name) { ChangeStrategy("co", name); }
        virtual void ChangeNonCombatStrategy(const char* name) { ChangeStrategy("nc", name); }

    private:
        void ChangeStrategy(const char* type, const char* name);

    public:
        string *buffer;
    };

}