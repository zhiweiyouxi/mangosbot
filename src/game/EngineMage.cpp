#include "pchdef.h"
#include "Action.h"
#include "Queue.h"
#include "EngineMage.h"
namespace ai
{

void EngineMage::Init()
{
	queue.Push(new ActionBasket(new CastFrostBoltAction(ai), 1.0f));
}

ActionBasket** CastFrostBoltAction::GetAfterActions()
{
	ActionBasket** actions = new ActionBasket*[1];
	actions[0] = new ActionBasket(new CastFrostBoltAction(ai), 1.0f);
	return actions;
}

}