#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"

using namespace std;

namespace ai 
{

class AiSpellManager : public AiManagerBase
{
public:
	AiSpellManager(PlayerbotAIBase* ai) : AiManagerBase(ai)
	{
		lastSpellId = 0;
		lastSpellTarget = 0;
		lastCastTime = 0;
	}

public:
	uint32 GetSpellId(const char* args);

public:
	bool CanCastSpell(const char* name, Unit* target)
	{
		return CanCastSpell(GetSpellId(name), target);
	}

public:
	bool CastSpell(const char* name, Unit* target) 
	{
		return CastSpell(GetSpellId(name), target);
	}

public:
	bool HasAura(uint32 spellId, const Unit& player);
	bool HasAura(const char* spellName) 
	{
		return HasAura(spellName, *bot);
	}
	bool HasAura(const char* spellName, const Unit& player) 
	{
		uint32 spellId = GetSpellId(spellName);
		return (spellId) ? HasAura(spellId, player) : false;
	}

private:
	uint32 FindSpellId(const char* args);
	bool CanCastSpell(uint32 spellid, Unit* target);
	bool CastSpell(uint32 spellId, Unit* target);

public:
	uint32 GetLastSpellId() { return lastSpellId; }
	uint64 GetLastSpellTarget() { return lastSpellTarget; }

public:
	void InterruptSpell();

private:
	std::map<std::string, uint32> spellMap;

	uint32 lastSpellId;
	uint64 lastSpellTarget;
	time_t lastCastTime;
};

};