#pragma once
#include "Action.h"
#include "PlayerbotAIFacadeAware.h"

namespace ai
{
    class Trigger : public PlayerbotAIFacadeAware
	{
	public:
        Trigger(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~Trigger() {}

	public:
		virtual BOOL IsActive() = NULL;
        virtual NextAction* getNextAction() { return NULL; }
        virtual NextAction** getNextActions();

	};
}
