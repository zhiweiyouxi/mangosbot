#include "ActionBasket.h"

#pragma once
namespace ai
{
class Queue
{
public:
	Queue(void);
public:
	~Queue(void);
public:
	void Push(Action *action, float relevance);
	Action* Pop();
private:
	std::list<ActionBasket*> actions;
};
}