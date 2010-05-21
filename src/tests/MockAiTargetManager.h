#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"
#include "AiTargetManager.h"
#include "AiSpellManager.h"
#include "AiStatsManager.h"

namespace ai
{
    class MockAiTargetManager : public AiTargetManager
    {
    public:
		MockAiTargetManager(PlayerbotAIBase* ai, AiSpellManager* spellManager, AiStatsManager* statsManager) : 
		  AiTargetManager(ai, spellManager, statsManager) 
		  {
			  deadPartyMember = false;
			  partyMemberWithoutAura = false;
			  haveTarget = true;
			  hasPet = true;
          }

	public:
		virtual Unit* GetPartyMemberWithoutAura(const char* spell);
		virtual Unit* GetPartyMinHealthPlayer();
		virtual Unit* GetDeadPartyMember();
		virtual Unit* GetPartyMemberToDispell(uint32 dispelType);
		virtual Unit* FindBiggerThreat();
		virtual Unit* FindLeastThreat();
		virtual Unit* GetCurrentTarget();
		virtual Player* GetSelf();
		virtual Unit* GetPet();
		virtual Player* GetMaster();

	public:
		static MockAiTargetManager* Instance();

	public:
		bool haveTarget;
		bool hasPet;
		bool partyMemberWithoutAura;
		bool deadPartyMember;
    };

}