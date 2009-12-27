#include "pchdef.h"
#include "Queue.h"
namespace ai
{
Queue::Queue(void)
{
}

Queue::~Queue(void)
{
}

void Queue::Push(Action *action, float relevance)
{
	actions.push_back(new ActionBasket(action, relevance));
}

Action* Queue::Pop()
{
	float max = -1;
	ActionBasket* selection = NULL;
	for (std::list<ActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
	{
		ActionBasket* basket = *iter;
		if (basket->getRelevance() > max)
		{
			max = basket->getRelevance();
			selection = basket;
		}
	}
	if (selection != NULL)
	{
		Action* action = selection->getAction();
		actions.remove(selection);
		delete selection;
		return action;
	}
	return NULL;
}


}