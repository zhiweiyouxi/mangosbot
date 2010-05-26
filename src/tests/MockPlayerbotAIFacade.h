#pragma once

#include "PlayerbotAIFacade.h"
#include "string"
#include "MockAiStatsManager.h"
#include "MockAiSpellManager.h"
#include "MockAiTargetManager.h"
#include "MockAiMoveManager.h"
#include "MockAiInventoryManager.h"
#include "MockAiManagerRegistry.h"

namespace ai
{
    class MockPlayerbotAIFacade : public PlayerbotAIFacade, PlayerbotAIBase
    {
    public:
        MockPlayerbotAIFacade() : PlayerbotAIFacade(NULL), PlayerbotAIBase(NULL, NULL)
        { 
			aiRegistry = new MockAiManagerRegistry(this, &buffer);

        }

		virtual ~MockPlayerbotAIFacade() 
		{
			delete aiRegistry;
		}

		AiSpellManager* GetSpellManager() { return aiRegistry->GetSpellManager(); }
		AiTargetManager* GetTargetManager() { return aiRegistry->GetTargetManager(); }
		AiStatsManager* GetStatsManager() { return aiRegistry->GetStatsManager(); }
		AiMoveManager* GetMoveManager() { return aiRegistry->GetMoveManager(); }
		AiInventoryManager* GetInventoryManager() { return aiRegistry->GetInventoryManager(); }

        virtual void Attack(Unit* target);
        virtual void TellMaster(const char* text) { buffer.append(text); }
        virtual void Emote(uint32 emote) { buffer.append(">emote"); }


        std::string buffer;
    
		AiManagerRegistry* aiRegistry;
	};

}