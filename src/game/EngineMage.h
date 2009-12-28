#pragma once;
#include "Engine.h"
#include "Action.h"
namespace ai
{
class EngineMage : public Engine
{
public:
	EngineMage(Player* const master, Player* const bot, PlayerbotAI* const ai);
	virtual ~EngineMage(void);

public:
	void Init();
};

class CastFrostBoltAction : public CastSpellAction
{
public:
	CastFrostBoltAction(PlayerbotAI* const ai);
	ActionBasket** GetAfterActions();
};
}