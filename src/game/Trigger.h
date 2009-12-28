#pragma once
#include "Action.h"
#include "PlayerBotAiAware.h"

namespace ai
{
    class Trigger : public PlayerBotAiAware
	{
	public:
        Trigger(PlayerbotAI* const ai) : PlayerBotAiAware(ai) {}
        virtual ~Trigger() {}

	public:
		virtual BOOL IsActive() = NULL;
		virtual ActionBasket** CreateHandlers() = NULL;

	};
}
