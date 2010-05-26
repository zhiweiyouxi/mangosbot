#pragma once

#include "AiManagerRegistry.h"
#include "string"

namespace ai
{
	class EverythingUnavailableAiSpellManager : public MockAiSpellManager 
	{
	public:
		EverythingUnavailableAiSpellManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry, string *buffer) :
		  MockAiSpellManager(ai, aiRegistry, buffer) {}

		  virtual bool CanCastSpell(const char* name, Unit* target) { return false; }
	};

    class EverythingUnavailableAiManagerRegistry : public MockAiManagerRegistry
    {
    public:
        EverythingUnavailableAiManagerRegistry() : MockAiManagerRegistry()
		{
			if (spellManager) delete spellManager;
			spellManager = new EverythingUnavailableAiSpellManager(&ai, this, &buffer);
		}
    };

}