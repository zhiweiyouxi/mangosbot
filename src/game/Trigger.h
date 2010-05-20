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
        virtual bool IsActive();

#define END_TRIGGER() \
    };

namespace ai
{
    class Trigger : public PlayerbotAIFacadeAware
	{
	public:
        Trigger(PlayerbotAIFacade* const ai, const char* name = NULL, int checkInterval = 1) : PlayerbotAIFacadeAware(ai) {
            this->name = name;
			this->checkInterval = checkInterval;
			ticksElapsed = 0;
			this->spellManager = ai->GetSpellManager();
			this->targetManager = ai->GetTargetManager();
			this->statsManager = ai->GetStatsManager();
        }
        virtual ~Trigger() {}

	public:
		virtual bool IsActive() = NULL;
        virtual NextAction** getHandlers() { return NULL; }
        virtual const char* getName() { return name ? name : "trigger"; }
		
		bool needCheck() {
			if (++ticksElapsed >= checkInterval) {
				ticksElapsed = 0;
				return true;
			}
			return false;
		}

    protected:
        const char* name;
		int checkInterval;
		int ticksElapsed;
		AiSpellManager* spellManager;
		AiTargetManager* targetManager;
		AiStatsManager* statsManager;
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
        bool IsActive() { return trigger->IsActive(); }
		bool needCheck() { return trigger->needCheck(); }
        Trigger* getTrigger() { return trigger; }
        const char* getName() { return trigger->getName(); }

    public:
        NextAction** getHandlers() { return NextAction::merge(NextAction::clone(handlers), trigger->getHandlers()); }

    private:
        Trigger* trigger;
        NextAction** handlers;
    };
}
