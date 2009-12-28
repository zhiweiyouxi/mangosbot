#pragma once
#include "Action.h"

namespace ai
{

	class Trigger
	{
	public:
		Trigger(PlayerbotAI* const ai);
		virtual ~Trigger();

	public:
		virtual BOOL IsActive() = NULL;
		virtual ActionBasket** CreateHandlers() = NULL;

	protected:
		PlayerbotAI* ai;
	};
}
