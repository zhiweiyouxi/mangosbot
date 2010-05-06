#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(ArcaneIntellectOnPartyTrigger, "arcane intellect", "arcane intellect on party")
    BUFF_TRIGGER(ArcaneIntellectTrigger, "arcane intellect", "arcane intellect")

	class NoFoodTrigger : public Trigger {
	public:
		NoFoodTrigger(PlayerbotAIFacade* const ai) : Trigger(ai, "no food trigger") {}
		virtual bool IsActive() { return !ai->HasFood(); }
	};
	
	class NoDrinkTrigger : public Trigger {
	public:
		NoDrinkTrigger(PlayerbotAIFacade* const ai) : Trigger(ai, "no drink trigger") {}
		virtual bool IsActive() { return !ai->HasDrink(); }
	};
}