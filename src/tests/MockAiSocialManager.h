#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiSocialManager.h"

namespace ai
{
    class MockAiSocialManager : public AiSocialManager
    {
    public:
        MockAiSocialManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry, string *buffer) : AiSocialManager(ai, aiRegistry) 
        {
			this->buffer = buffer;
		}

	public:
		virtual void Emote(uint32 emote);
		virtual void TellMaster(const char* text);

	private:
		string *buffer;

    };

}