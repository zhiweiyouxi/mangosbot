#pragma once

#include "Player.h"
#include "Engine.h"
#include "AiManagerRegistry.h"

using namespace ai;

class AiFactory
{
public:
	static Engine* createCombatEngine(Player* player, AiManagerRegistry* const facade);
	static Engine* createNonCombatEngine(Player* player, AiManagerRegistry* const facade);
};
