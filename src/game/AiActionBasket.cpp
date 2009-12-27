#include "pchdef.h"
#include "AiActionBasket.h"

AiActionBasket::AiActionBasket(AiAction* action, float relevance)
{
	this->action = action;
	this->relevance = relevance;
}

AiActionBasket::~AiActionBasket(void)
{
}
