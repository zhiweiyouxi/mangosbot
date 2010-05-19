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
		virtual uint32 GetSpellId(const char* args);
		virtual void InterruptSpell();
		virtual void RemoveAura(const char* name);

		virtual bool CanCastSpell(const char* name, Unit* target)
		{
			return CanCastSpell(GetSpellId(name), target);
		}

		virtual bool CastSpell(const char* name, Unit* target) 
		{
			return CastSpell(GetSpellId(name), target);
		}

		virtual bool HasAura(const char* spellName, const Unit* player) 
		{
			return HasAura(GetSpellId(spellName), player);
		}

	private:
		uint32 FindSpellId(const char* args);
		bool HasAura(uint32 spellId, const Unit* player);
		bool CanCastSpell(uint32 spellid, Unit* target);
		bool CastSpell(uint32 spellId, Unit* target);

	public:
		uint32 GetLastSpellId() { return lastSpellId; }
		uint64 GetLastSpellTarget() { return lastSpellTarget; }

	private:
		std::map<std::string, uint32> spellMap;

		uint32 lastSpellId;
		uint64 lastSpellTarget;
		time_t lastCastTime;
	};

};