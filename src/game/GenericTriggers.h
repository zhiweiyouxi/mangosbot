#pragma once
#include "Trigger.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : BuffTrigger(ai, spell) {} \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : BuffOnPartyTrigger(ai, spell) {}  \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(AiManagerRegistry* const ai) : DebuffTrigger(ai, spell) {} \
    };

namespace ai
{
	class StatAvailable : public Trigger
	{
	public:
		StatAvailable(AiManagerRegistry* const ai, int amount) : Trigger(ai) 
		{
			this->amount = amount;
		}

	protected:
		int amount;
	};

	class RageAvailable : public StatAvailable
    {
    public:
        RageAvailable(AiManagerRegistry* const ai, int amount) : StatAvailable(ai, amount) {}
        virtual bool IsActive();
    };

	class EnergyAvailable : public StatAvailable
	{
	public:
		EnergyAvailable(AiManagerRegistry* const ai, int amount) : StatAvailable(ai, amount) {}
		virtual bool IsActive();
	};

	class ComboPointsAvailable : public StatAvailable
	{
	public:
		ComboPointsAvailable(AiManagerRegistry* const ai, int amount) : StatAvailable(ai, amount) {}
		virtual bool IsActive();
	};

	class LoseAggroTrigger : public Trigger {
	public:
		LoseAggroTrigger(AiManagerRegistry* const ai) : Trigger(ai, "lose aggro") {}
		virtual bool IsActive();
	};

	class SpellTrigger : public Trigger
	{
	public:
		SpellTrigger(AiManagerRegistry* const ai, const char* spell, int checkInterval = 1) : Trigger(ai, spell, checkInterval) 
		{
			this->spell = spell;
		}

		virtual Unit* GetTarget();
		virtual const char* getName() { return spell; }
		virtual bool IsActive();

	protected:
		const char* spell;
	};

	class SpellCanBeCastTrigger : public SpellTrigger 
	{
	public:
		SpellCanBeCastTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell) {}
		virtual bool IsActive();
	};

	// TODO: check other targets
    class InterruptSpellTrigger : public SpellTrigger 
	{
    public:
        InterruptSpellTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell) {}
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };


    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(AiManagerRegistry* const ai, int amount, float distance = BOT_REACT_DISTANCE) : Trigger(ai) 
        {
            this->amount = amount;
            this->distance = distance;
        }
    public: 
        virtual bool IsActive() 
		{
            return statsManager->GetAttackerCount(distance) >= amount;
        }
        virtual const char* getName() { return "attacker count"; }

    protected:
        int amount;
        float distance;
    };    

    class MyAttackerCountTrigger : public AttackerCountTrigger
    {
    public:
        MyAttackerCountTrigger(AiManagerRegistry* const ai, int amount) : AttackerCountTrigger(ai, amount) {}
    public: 
        virtual bool IsActive();
        virtual const char* getName() { return "my attacker count"; }
    };    

    class BuffTrigger : public SpellTrigger
    {
    public:
        BuffTrigger(AiManagerRegistry* const ai, const char* spell) : SpellTrigger(ai, spell, 5) {}
    public: 
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };

    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {}
    public: 
		virtual Unit* GetTarget();
    };

    BEGIN_TRIGGER(NoAttackersTrigger, Trigger)
    END_TRIGGER()

    class DebuffTrigger : public BuffTrigger
    {
    public:
        DebuffTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {
			checkInterval = 1;
		}
    public: 
		virtual Unit* GetTarget();
        virtual bool IsActive();
    };

    BEGIN_TRIGGER(LootAvailableTrigger, Trigger)
    END_TRIGGER()


	class BoostTrigger : public BuffTrigger
	{
	public:
		BoostTrigger(AiManagerRegistry* const ai, const char* spell, float balance) : BuffTrigger(ai, spell) 
		{
			this->balance = balance;
		}
	public: 
		virtual bool IsActive();

	protected:
		float balance;
	};

    class RandomTrigger : public Trigger
    {
    public:
        RandomTrigger(AiManagerRegistry* const ai, int probability) : Trigger(ai) 
        {
            this->probability = probability;
        }
    public: 
        virtual bool IsActive();
        virtual const char* getName() { return "random"; }

    protected:
        int probability;
    };

    class AndTrigger : public Trigger
    {
    public:
        AndTrigger(AiManagerRegistry* const ai, Trigger* ls, Trigger* rs) : Trigger(ai) 
        {
            this->ls = ls;
            this->rs = rs;
        }
        virtual ~AndTrigger() 
        {
            delete ls;
            delete rs;
        }
    public: 
        virtual bool IsActive();
        virtual const char* getName();

    protected:
        Trigger* ls;
        Trigger* rs;
    };

    class SnareTargetTrigger : public DebuffTrigger
    {
    public:
        SnareTargetTrigger(AiManagerRegistry* const ai, const char* aura) : DebuffTrigger(ai, aura) {}
    public: 
        virtual bool IsActive();
        virtual const char* getName() { return "target is moving"; }
    };

	class LowManaTrigger : public Trigger 
	{
	public:
		LowManaTrigger(AiManagerRegistry* const ai) : Trigger(ai, "low mana", 5) {}

		virtual bool IsActive();
	};

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
    END_TRIGGER()


	class NoPetTrigger : public Trigger 
	{
	public:
		NoPetTrigger(AiManagerRegistry* const ai) : Trigger(ai, "no pet", 5) {}

		virtual bool NoPetTrigger::IsActive() {
			return !targetManager->GetPet() && !ai->GetStatsManager()->IsMounted();
		}
	};

	class ItemCountTrigger : public Trigger {
	public:
		ItemCountTrigger(AiManagerRegistry* const ai, const char* item, int count) : Trigger(ai, item, 5) {
			this->item = item;
			this->count = count;
		}
	public: 
		virtual bool IsActive();
		virtual const char* getName() { return "item count"; }

	protected:
		const char* item;
		int count;
	};

	class HasAuraTrigger : public Trigger {
	public:
		HasAuraTrigger(AiManagerRegistry* const ai, const char* spell) : Trigger(ai, spell) {
			this->spell = spell;
		}

		virtual Unit* GetTarget();
		virtual bool IsActive();

	protected:
		const char* spell;
	};
}

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"
