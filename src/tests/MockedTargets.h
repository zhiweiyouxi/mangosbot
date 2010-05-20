#pragma once

#include "string"
#include "Unit.h"

using namespace std;

namespace ai
{
    class MockedTargets 
    {
	public:
		static Unit* GetPartyMember() { return (Unit*)1; }
		static Unit* GetCurrentTarget()  { return (Unit*)7; }
		static Unit* GetSelf() { return (Unit*)9; }
		static Unit* GetPet() { return (Unit*)10; }
   };

}