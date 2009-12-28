#pragma once

namespace ai
{
	class ActionBasket;

	class Action
	{
	public:
		Action(PlayerbotAI* const ai);

		virtual void Execute() {}
		virtual ActionBasket** GetAfterActions() {return NULL;}
	public:
		virtual ~Action(void);

	protected:
		PlayerbotAI* ai;
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

	class ActionBasket
	{
	public:
		ActionBasket(Action* action, float relevance);
		~ActionBasket(void);
	public:
		float getRelevance() {return relevance;}
		Action* getAction() {return action;}
	private:
		Action* action;
		float relevance;
	};
}