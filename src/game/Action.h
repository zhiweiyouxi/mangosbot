#pragma once
#include "PlayerbotAIFacadeAware.h"


#define BEGIN_ACTION(clazz, name) \
class clazz : public Action \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : Action(ai) {} \
        virtual void Execute(); \
        virtual const char* getName() { return name; }

#define ACTION_KIND(value) \
    virtual int getKind() { return value; }

#define END_ACTION() \
    };


#define BEGIN_NEXT_ACTIONS(size) \
    NextAction** getNextActions() \
    { \
    NextAction** actions = new NextAction*[size + 1];

#define NEXT_ACTION(index, name, relevance) \
    actions[index] = new NextAction(name, relevance);

#define END_NEXT_ACTIONS(size) \
    actions[size] = NULL; \
    return actions; \
    }


#define ALTERNATIVE_ACTIONS(name) \
    virtual NextAction* getAlternativeAction() { return new NextAction(name, 0.0f); }

#define BEGIN_ALTERNATIVE_ACTIONS(size) \
    NextAction** getAlternativeActions() \
    { \
    NextAction** actions = new NextAction*[size + 1];

#define ALTERNATIVE_ACTION(index, name) \
    actions[index] = new NextAction(name, 0.0f);

#define END_ALTERNATIVE_ACTIONS(size) \
    actions[size] = NULL; \
    return actions; \
    }

#define PREREQUISITE_ACTIONS(name) \
    virtual NextAction* getPrerequisiteAction() { return new NextAction(name, 0.0f); }

#define BEGIN_PREREQUISITE_ACTIONS(size) \
    NextAction** getPrerequisiteActions() \
    { \
    NextAction** actions = new NextAction*[size + 1];

#define PREREQUISITE_ACTION(index, name) \
    actions[index] = new NextAction(name, 0.0f);

#define END_PREREQUISITE_ACTIONS(size) \
    actions[size] = NULL; \
    return actions; \
    }

namespace ai
{
    class NextAction
    {
    public:
        NextAction(const char* name, float relevance)
        {
            this->name = name;
            this->relevance = relevance;
        }
        NextAction(const NextAction& o)
        {
            this->name = o.name;
            this->relevance = o.relevance;
        }

    public:
        const char* getName() { return name.c_str(); }
        float getRelevance() {return relevance;}

    public:
        static NextAction** clone(NextAction** actions);

    private:
        float relevance;
        std::string name;
    };
    
    //---------------------------------------------------------------------------------------------------------------------
    
    class ActionBasket;

    class Action : public PlayerbotAIFacadeAware
	{
	public:
        Action(PlayerbotAIFacade* const ai) : PlayerbotAIFacadeAware(ai) {}
        virtual ~Action(void) {}

    public:
        virtual void Execute() {}
        virtual BOOL isAvailable() { return TRUE; }
        virtual BOOL isUseful() { return TRUE; }
        virtual NextAction* getNextAction() { return NULL; }
        virtual NextAction** getNextActions();
        virtual NextAction* getAlternativeAction() { return NULL; }
        virtual NextAction** getAlternativeActions();
        virtual NextAction* getPrerequisiteAction() { return NULL; }
        virtual NextAction** getPrerequisiteActions();
        virtual const char* getName() { return "action"; }
        virtual int getKind() { return 0; }
	};

    class ActionNode
    {
    public:
        ActionNode(Action* action, NextAction** continuers = NULL, NextAction** alternatives = NULL, NextAction** prerequisites = NULL)
        {
            this->action = action; 
            this->continuers = continuers;
            this->alternatives = alternatives;
            this->prerequisites = prerequisites;
        }
        virtual ~ActionNode() { delete action; }

    public:
        Action* getAction() { return action; }

    public:
        NextAction** getContinuers() { return NextAction::clone(continuers); }
        NextAction** getAlternatives() { return NextAction::clone(alternatives); }
        NextAction** getPrerequisites() { return NextAction::clone(prerequisites); }

    private:
        NextAction** clone(NextAction** actions);

    private:
        Action* action;
        NextAction** continuers;
        NextAction** alternatives;
        NextAction** prerequisites;
    };

    //---------------------------------------------------------------------------------------------------------------------

	class ActionBasket
	{
	public:
		ActionBasket(Action* action, float relevance, BOOL skipPrerequisites = FALSE)
        {
            this->action = action;
            this->relevance = relevance;
            this->skipPrerequisites = skipPrerequisites;
        }
        virtual ~ActionBasket(void) {}
	public:
		float getRelevance() {return relevance;}
		Action* getAction() {return action;}
        BOOL isSkipPrerequisites() { return skipPrerequisites; }
        void AmendRelevance(float k) {relevance *= k; }
        void setRelevance(float relevance) { this->relevance = relevance; }
	private:
		Action* action;
		float relevance;
        BOOL skipPrerequisites;
	};

    //---------------------------------------------------------------------------------------------------------------------
    
   
}