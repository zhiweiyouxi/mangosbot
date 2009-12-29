#pragma once
#include "PlayerbotAIFacadeAware.h"

#define BEGIN_SPELL_ACTION(clazz, name) \
    class clazz : public CastSpellAction \
        { \
        public: \
            clazz(PlayerbotAIFacade* const ai) : CastSpellAction(ai, name) {} \

#define NEXT_ACTIONS(name, relevance) \
            virtual NextAction* getNextAction() { return new NextAction(name, relevance); }

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

#define END_SPELL_ACTION() \
    };

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
        virtual const char* getName() { return "action"; }
        virtual int getKind() { return 0; }
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
        virtual const char* getName() { return spell; }
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
        void setRelevance(float relevance) { this->relevance = relevance; }
	private:
		Action* action;
		float relevance;
	};

    //---------------------------------------------------------------------------------------------------------------------
    
   
}