#pragma once

namespace ai
{
    class NextAction
    {
    public:
        NextAction(const char* name, float relevance = 0.0f)
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
        static int size(NextAction** actions);
        static NextAction** clone(NextAction** actions);
        static NextAction** merge(NextAction** what, NextAction** with);
        static NextAction** array(uint8 nil,...);
        static void destroy(NextAction** actions);

    private:
        float relevance;
        std::string name;
    };
    
    //---------------------------------------------------------------------------------------------------------------------
    
    class ActionBasket;

    class Action : public AiManagerRegistryAware
	{
	public:
        Action(AiManagerRegistry* const ai, const char* name = NULL) : AiManagerRegistryAware(ai) {
            this->name = name;
        }
        virtual ~Action(void) {}

    public:
        virtual bool ExecuteResult() { Execute(); return TRUE; }
        virtual void Execute() { }
        virtual bool isPossible() { return TRUE; }
        virtual bool isUseful() { return TRUE; }
        virtual NextAction** getPrerequisites() { return NULL; }
        virtual NextAction** getAlternatives() { return NULL; }
        virtual NextAction** getContinuers() { return NULL; }
        virtual const char* getName() { return !name ? "action" : name; }
        virtual int getKind() { return 0; }

    protected:
        const char* name;
	};

    class ActionNode
    {
    public:
        ActionNode(Action* action, NextAction** prerequisites = NULL, NextAction** alternatives = NULL, NextAction** continuers = NULL)
        {
            this->action = action; 
            this->prerequisites = prerequisites;
            this->alternatives = alternatives;
            this->continuers = continuers;
        }
        virtual ~ActionNode() 
        { 
            delete action; 
            NextAction::destroy(prerequisites); 
            NextAction::destroy(alternatives); 
            NextAction::destroy(continuers); 
        }

    public:
        Action* getAction() { return action; }
        const char* getName() { return action->getName(); }
        virtual bool Execute() { return action->ExecuteResult(); }
        virtual bool isPossible() { return action->isPossible(); }
        virtual bool isUseful() { return action->isUseful(); }

    public:
        NextAction** getContinuers() { return NextAction::merge(NextAction::clone(continuers), action->getContinuers()); }
        NextAction** getAlternatives() { return NextAction::merge(NextAction::clone(alternatives), action->getAlternatives()); }
        NextAction** getPrerequisites() { return NextAction::merge(NextAction::clone(prerequisites), action->getPrerequisites()); }

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
		ActionBasket(ActionNode* action, float relevance, bool skipPrerequisites = FALSE)
        {
            this->action = action;
            this->relevance = relevance;
            this->skipPrerequisites = skipPrerequisites;
        }
        virtual ~ActionBasket(void) {}
	public:
		float getRelevance() {return relevance;}
		ActionNode* getAction() {return action;}
        bool isSkipPrerequisites() { return skipPrerequisites; }
        void AmendRelevance(float k) {relevance *= k; }
        void setRelevance(float relevance) { this->relevance = relevance; }
	private:
		ActionNode* action;
		float relevance;
        bool skipPrerequisites;
	};

    //---------------------------------------------------------------------------------------------------------------------
    
   
}