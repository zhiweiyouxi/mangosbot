#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "Item.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;

	class AiSocialManager : public AiManagerBase
	{
	public:
		AiSocialManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual void Emote(uint32 emote);

	};

};