#include "pchdef.h"
#include "AiQueue.h"

AiQueue::AiQueue(void)
{
}

AiQueue::~AiQueue(void)
{
}

void AiQueue::Push(AiAction *action, float relevance)
{
	actions.push_back(new AiActionBasket(action, relevance));
}

AiAction* AiQueue::Pop()
{
	float max = -1;
	AiActionBasket* selection = NULL;
	for (std::list<AiActionBasket*>::iterator iter = actions.begin(); iter != actions.end(); iter++)
	{
		AiActionBasket* basket = *iter;
		if (basket->getRelevance() > max)
		{
			max = basket->getRelevance();
			selection = basket;
		}
	}
	if (selection != NULL)
	{
		AiAction* action = selection->getAction();
		actions.remove(selection);
		delete selection;
		return action;
	}
	return NULL;
}
