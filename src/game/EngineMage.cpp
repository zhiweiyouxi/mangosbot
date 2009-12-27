#include "pchdef.h"
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
	queue.Push(new CastFrostBoltAction(ai), 1.0f);
}

CastFrostBoltAction::CastFrostBoltAction(PlayerbotAI* const ai) : CastSpellAction(ai, "frostbolt")
{
}

Action** CastFrostBoltAction::GetAfterActions()
{
	Action** actions = new Action*[1];
	actions[0] = new CastFrostBoltAction(ai);
	return actions;
}

}