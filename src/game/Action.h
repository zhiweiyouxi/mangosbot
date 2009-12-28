#pragma once
#include "PlayerBotAiAware.h"

namespace ai
{
	class ActionBasket;

    class Action : public PlayerBotAiAware
	{
	public:
        Action(PlayerbotAI* const ai) : PlayerBotAiAware(ai) {}
        virtual ~Action(void) {}

    public:
        virtual void Execute() {}
        virtual ActionBasket** GetAfterActions() { return NULL; }

	};

	//---------------------------------------------------------------------------------------------------------------------

	class CastSpellAction : public Action
	{
	public:
		CastSpellAction(PlayerbotAI* const ai, const char* spell);

		void Execute();
	private:
		uint32 spellid;
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
	private:
		Action* action;
		float relevance;
	};
}