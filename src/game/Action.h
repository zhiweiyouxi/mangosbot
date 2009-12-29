#pragma once
#include "PlayerbotAIFacadeAware.h"

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
        virtual NextAction* getNextAction() { return NULL; }
        virtual NextAction** getNextActions();
	};

	//---------------------------------------------------------------------------------------------------------------------

	class CastSpellAction : public Action
	{
	public:
        CastSpellAction(PlayerbotAIFacade* const ai, const char* spell) : Action(ai)
        {
            this->spell = spell;
        }

		void Execute();
        virtual BOOL isAvailable();
	private:
		const char* spell;
	};

    //---------------------------------------------------------------------------------------------------------------------

	class ActionBasket
	{
	public:
		ActionBasket(Action* action, float relevance)
        {
            this->action = action;
            this->relevance = relevance;
        }
        ~ActionBasket(void) {}
	public:
		float getRelevance() {return relevance;}
		Action* getAction() {return action;}
        void AmendRelevance(float k) {relevance *= k; }
	private:
		Action* action;
		float relevance;
	};

    //---------------------------------------------------------------------------------------------------------------------
    
   
}