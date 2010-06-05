#pragma once

class ai::AiManagerRegistry;
class Player;

using namespace ai;

class AiFactory
{
public:
	static Engine* createCombatEngine(Player* player, AiManagerRegistry* const facade);
	static Engine* createNonCombatEngine(Player* player, AiManagerRegistry* const facade);
};
