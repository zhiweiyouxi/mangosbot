#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"
#include "Multiplier.h"
#include "ActionFactory.h"

namespace ai
{
    class MANGOS_DLL_SPEC Engine : public PlayerbotAIFacadeAware
    {
    public:
        Engine(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}

	    void Init() { InitActionFactory(); InitQueue(); InitTriggers(); }
        virtual void InitTriggers() {}
        virtual void InitQueue() {}
        virtual void InitActionFactory() { actionFactory = new ActionFactory(ai); }
	    virtual BOOL DoNextAction(Unit*);

    public:
	    virtual ~Engine(void);

    private:
        void MultiplyAndPush(NextAction** actions);

    protected:
	    Queue queue;
	    std::list<Trigger*> triggers;
        std::list<Multiplier*> multipliers;
	    Player* master;
	    Player* bot;
        ActionFactory* actionFactory;
    };
}