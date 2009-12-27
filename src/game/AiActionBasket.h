#include "AiAction.h"
#pragma once

class AiActionBasket
{
public:
	AiActionBasket(AiAction* action, float relevance);
public:
	~AiActionBasket(void);
public:
	float getRelevance() {return relevance;}
	AiAction* getAction() {return action;}
private:
	AiAction* action;
	float relevance;
};

