#include "Action.h"
#pragma once
namespace ai
{
	class ActionBasket
	{
	public:
		ActionBasket(Action* action, float relevance);
	public:
		~ActionBasket(void);
	public:
		float getRelevance() {return relevance;}
		Action* getAction() {return action;}
	private:
		Action* action;
		float relevance;
	};

}