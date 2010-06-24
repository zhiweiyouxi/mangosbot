#pragma once

namespace ai
{
	class EverythingUnavailableAiSpellManager : public MockAiSpellManager 
	{
	public:
		EverythingUnavailableAiSpellManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry, string *buffer) :
		  MockAiSpellManager(ai, aiRegistry, buffer) {}

		  virtual bool CanCastSpell(const char* name, Unit* target) { return false; }
	};

    class EverythingUnavailableAiManagerRegistry : public MockAiManagerRegistry
    {
    public:
        EverythingUnavailableAiManagerRegistry() : MockAiManagerRegistry()
		{
			managers[AiSpellManagerType] = new EverythingUnavailableAiSpellManager(&ai, this, &buffer);
		}
    };

}