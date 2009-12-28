#include "pchdef.h"
#include "Action.h"
#include "Queue.h"

namespace ai
{
Queue::Queue(void)
{
}

Queue::~Queue(void)
{
}

void Queue::Push(ActionBasket *action)
{
	if (action)
		actions.push_back(action);
}

void Queue::Push(ActionBasket **actions)
{
	if (actions)
	{
		for (int i=0; i<sizeof(actions)/sizeof(ActionBasket*); i++)
		{
			Push(actions[i]);
		}
	}
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