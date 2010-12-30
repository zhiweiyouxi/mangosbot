#pragma once

#include "GenericHunterStrategy.h"
#include "../GenericNonCombatStrategy.h"

namespace ai
{
	class HunterBuffDpsStrategy : public GenericNonCombatStrategy
	{
	public:
		HunterBuffDpsStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
		virtual const char* getName() { return "bdps"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual string GetIncompatibleStrategies() { return "-rnature"; }
	};

	class HunterNatureResistanceStrategy : public GenericNonCombatStrategy
	{
	public:
		HunterNatureResistanceStrategy(AiManagerRegistry* const ai) : GenericNonCombatStrategy(ai) {}
		virtual const char* getName() { return "rnature"; }

	public:
		virtual void InitTriggers(std::list<TriggerNode*> &triggers);
		virtual string GetIncompatibleStrategies() { return "-bdps"; }
	};
}