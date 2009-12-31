#pragma once
#include "PlayerbotAIFacadeAware.h"

#define BEGIN_SPELL_ACTION(clazz, name) \
    class clazz : public CastSpellAction \
        { \
        public: \
            clazz(PlayerbotAIFacade* const ai) : CastSpellAction(ai, name) {} \


#define END_SPELL_ACTION() \
    };

#define BEGIN_RANGED_SPELL_ACTION(clazz, name) \
class clazz : public CastRangedSpellAction \
        { \
        public: \
        clazz(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, name) {} \


#define END_RANGED_SPELL_ACTION() \
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


#define ALTERNATIVE_ACTIONS(name, relevance) \
    virtual NextAction* getAlternativeAction() { return new NextAction(name, relevance); }

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

    class CastRangedSpellAction : public CastSpellAction
    {
    public:
        CastRangedSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}

        PREREQUISITE_ACTIONS("reach spell");

    private:
        const char* spell;
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