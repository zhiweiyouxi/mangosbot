#include "pchdef.h"
#include "Action.h"
#include "Queue.h"
#include "EngineMage.h"
namespace ai
{
EngineMage::EngineMage(Player* const master, Player* const bot, PlayerbotAI* const ai) : Engine(master, bot, ai)
{
}

EngineMage::~EngineMage(void)
{
}

void EngineMage::Init()
{
	queue.Push(new ActionBasket(new CastFrostBoltAction(ai), 1.0f));
}

CastFrostBoltAction::CastFrostBoltAction(PlayerbotAI* const ai) : CastSpellAction(ai, "frostbolt")
{
}

ActionBasket** CastFrostBoltAction::GetAfterActions()
{
	ActionBasket** actions = new ActionBasket*[1];
	actions[0] = new ActionBasket(new CastFrostBoltAction(ai), 1.0f);
	return actions;
}

}