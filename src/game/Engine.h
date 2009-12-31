#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"
#include "Multiplier.h"
#include "ActionFactory.h"
#include "Strategy.h"

namespace ai
{
    class MANGOS_DLL_SPEC Engine : public PlayerbotAIFacadeAware
    {
    public:
        Engine(PlayerbotAIFacade* const ai, ActionFactory *factory) : PlayerbotAIFacadeAware(ai) 
        {
            actionFactory = factory;
        }

	    void Init();
        void addStrategy(const char* name);
        void removeStrategy(const char* name);
        void clearStrategies();

    public:
	    virtual BOOL DoNextAction(Unit*);
        void ExecuteAction(const char* name);

    public:
	    virtual ~Engine(void);

    private:
        BOOL MultiplyAndPush(NextAction** actions, float forceRelevance = 0.0f, BOOL skipPrerequisites = FALSE);
        void Reset();

    protected:
	    Queue queue;
	    std::list<Trigger*> triggers;
        std::list<Multiplier*> multipliers;
	    Player* master;
	    Player* bot;
        ActionFactory* actionFactory;
        std::list<Strategy*> strategies;
    };
}