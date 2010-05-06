#pragma once

#include "Action.h"
#include "Queue.h"
#include "Trigger.h"
#include "Multiplier.h"
#include "ActionFactory.h"
#include "Strategy.h"

namespace ai
{
    class ActionExecutionListener 
    {
    public:
        virtual bool ActionExecuted(Action* action) = NULL;
    };

    // -----------------------------------------------------------------------------------------------------------------------

    class ActionExecutionListeners : public ActionExecutionListener
    {
    public:
        virtual ~ActionExecutionListeners();

    // ActionExecutionListener
    public:
        virtual bool ActionExecuted(Action* action);

    public:
        void Add(ActionExecutionListener* listener)
        {
            listeners.push_back(listener);
        }
        void Remove(ActionExecutionListener* listener)
        {
            listeners.remove(listener);
        }

    private:
        std::list<ActionExecutionListener*> listeners;
    };

    // -----------------------------------------------------------------------------------------------------------------------

    class Engine : public PlayerbotAIFacadeAware
    {
    public:
        Engine(PlayerbotAIFacade* const ai, ActionFactory *factory) : PlayerbotAIFacadeAware(ai) 
        {
            actionFactory = factory;
            lastRelevance = 0.0f;
            maxIterations = 10;
			testMode = false;
        }

	    void Init();
        void addStrategy(const char* name);
        void removeStrategy(const char* name);
        void clearStrategies();
        std::string ListStrategies();

    public:
	    virtual bool DoNextAction(Unit*, int depth = 0);
        void ExecuteAction(const char* name);

    public:
        void AddActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Add(listener);
        }
        void removeActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Remove(listener);
        }

    public:
	    virtual ~Engine(void);

    private:
        bool MultiplyAndPush(NextAction** actions, float forceRelevance = 0.0f, bool skipPrerequisites = FALSE);
        void Reset();
        void ProcessTriggers();
        void PushDefaultActions();
        void PushAgain(ActionNode* actionNode, float relevance);
        ActionNode* createAction(const char* name);

    protected:
	    Queue queue;
	    std::list<TriggerNode*> triggers;
        std::list<Multiplier*> multipliers;
	    Player* master;
	    Player* bot;
        ActionFactory* actionFactory;
        std::list<Strategy*> strategies;
        float lastRelevance;

    public:
        int maxIterations;
		bool testMode;

    private:
        ActionExecutionListeners actionExecutionListeners;
    };
}