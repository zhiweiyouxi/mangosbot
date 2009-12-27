#include "AiActionBasket.h"
#pragma once

class AiQueue
{
public:
	AiQueue(void);
public:
	~AiQueue(void);
public:
	void Push(AiAction *action, float relevance);
	AiAction* Pop();
private:
	std::list<AiActionBasket*> actions;
};

