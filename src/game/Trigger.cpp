#include "pchdef.h"
#include "Trigger.h"
#include "Action.h"

namespace ai
{
	Trigger::Trigger(PlayerbotAI* const ai)
	{
		this->ai = ai;
	}

	Trigger::~Trigger()
	{
	}
}