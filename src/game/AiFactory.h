#pragma once

#include "Player.h"
#include "Engine.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

class AiFactory
{
public:
	static Engine* createCombatEngine(Player* player, PlayerbotAIFacade* const facade);
	static Engine* createNonCombatEngine(Player* player, PlayerbotAIFacade* const facade);
};
