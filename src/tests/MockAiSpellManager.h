#pragma once

#include "AiSpellManager.h"
#include "string"

using namespace std;
using namespace ai;

namespace ai
{
    class MockAiSpellManager : public AiSpellManager
    {
    public:
        MockAiSpellManager(PlayerbotAIBase* ai, string *buffer) : AiSpellManager(ai) 
        { 
            targetIsCastingNonMeleeSpell = false;
			this->buffer = buffer;
        }

	public:
		virtual uint32 GetSpellId(const char* args) { return 1; }
		virtual void InterruptSpell();
		virtual void RemoveAura(const char* name);
		virtual bool CanCastSpell(const char* name, Unit* target);
		virtual bool CastSpell(const char* name, Unit* target);
		virtual bool HasAura(const char* spellName, Unit* player);
		virtual bool IsSpellCasting(Unit* player);
		virtual bool HasAuraToDispel(Unit* player, uint32 dispelType);

    public:
        void resetSpells() {spellCooldowns.clear(); }

	public:
        string *buffer;
        
	public:
		list<string> spellCooldowns;
        
		map<Unit*, list<string>> auras;
		map<Unit*, uint32> dispels;
        
		bool targetIsCastingNonMeleeSpell;
    };

}