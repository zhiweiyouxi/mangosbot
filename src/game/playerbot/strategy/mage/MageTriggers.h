#pragma once
#include "../GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(ArcaneIntellectOnPartyTrigger, "arcane intellect", "arcane intellect on party")
    BUFF_TRIGGER(ArcaneIntellectTrigger, "arcane intellect", "arcane intellect")

	class NoFoodTrigger : public Trigger {
	public:
		NoFoodTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no food trigger") {}
		virtual bool IsActive() { return !ai->GetInventoryManager()->HasFood(); }
	};
	
	class NoDrinkTrigger : public Trigger {
	public:
		NoDrinkTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no drink trigger") {}
		virtual bool IsActive() { return !ai->GetInventoryManager()->HasDrink(); }
	};

    class MageArmorTrigger : public BuffTrigger {
    public:
        MageArmorTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "mage armor") {}
        virtual bool IsActive();
    };
    
    class FireballTrigger : public DebuffTrigger {
    public:
        FireballTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "fireball") {}
	};

    class PyroblastTrigger : public DebuffTrigger {
    public:
        PyroblastTrigger(AiManagerRegistry* const ai) : DebuffTrigger(ai, "pyroblast") {}
    };
}