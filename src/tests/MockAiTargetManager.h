#pragma once

#include "string"

using namespace std;

#include "MockedTargets.h"

namespace ai
{
    class MockAiTargetManager : public AiTargetManager
    {
    public:
		MockAiTargetManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : 
		  AiTargetManager(ai, aiRegistry) 
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
		virtual Unit* GetCurrentTarget();
		virtual Unit* FindTargetForTank();
		virtual Unit* FindTargetForDps();
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