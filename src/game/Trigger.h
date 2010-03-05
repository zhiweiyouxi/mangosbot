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
        Trigger(PlayerbotAIFacade* const ai, const char* name = NULL) : PlayerbotAIFacadeAware(ai) {
            this->name = name;
        }
        virtual ~Trigger() {}

	public:
		virtual BOOL IsActive() = NULL;
        virtual NextAction** getHandlers() { return NULL; }
        virtual const char* getName() { return name ? name : "trigger"; }

    protected:
        const char* name;
	};


    class TriggerNode
    {
    public:
        TriggerNode(Trigger* trigger, NextAction** handlers = NULL)
        {
            this->trigger = trigger; 
            this->handlers = handlers;
        }
        virtual ~TriggerNode() 
        { 
            delete trigger; 
            NextAction::destroy(handlers); 
        }

    public:
        BOOL IsActive() { return trigger->IsActive(); }
        Trigger* getTrigger() { return trigger; }
        const char* getName() { return trigger->getName(); }

    public:
        NextAction** getHandlers() { return NextAction::merge(NextAction::clone(handlers), trigger->getHandlers()); }

    private:
        Trigger* trigger;
        NextAction** handlers;
    };
}
