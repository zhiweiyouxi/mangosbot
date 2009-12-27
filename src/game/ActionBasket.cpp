#include "pchdef.h"
#include "ActionBasket.h"
namespace ai
{

ActionBasket::ActionBasket(Action* action, float relevance)
{
	this->action = action;
	this->relevance = relevance;
}

ActionBasket::~ActionBasket(void)
{
}

}