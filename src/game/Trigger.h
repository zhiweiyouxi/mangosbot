#pragma once
#include "Action.h"
#include "PlayerbotAIFacadeAware.h"

#define NEXT_TRIGGERS(name, relevance) \
    virtual NextAction* getNextAction() { return new NextAction(name, relevance); }

#define BEGIN_TRIGGER(clazz, super) \
class clazz : public super \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : super(ai) {} \
    public: \
        virtual BOOL IsActive();

#define END_TRIGGER() \
    };

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
        virtual const char* getName() { return "Trigger"; }

	};
}
