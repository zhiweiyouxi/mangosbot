#pragma once

#include "string"
#include "Unit.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"


using namespace std;

namespace ai
{
    class MockedTargets 
    {
	public:
		static Unit* GetPartyMember() { return (Unit*)1; }
		static Unit* GetCurrentTarget()  { return (Unit*)7; }
		static Player* GetSelf() { return (Player*)9; }
		static Unit* GetPet() { return (Unit*)10; }
		static Player* GetMaster() { return (Player*)2; }
        static Player* GetTargetForDps() { return (Player*)3; }
        static Player* GetTargetForTank() { return (Player*)4; }
   };

}