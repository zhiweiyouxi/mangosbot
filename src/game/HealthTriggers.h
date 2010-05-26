#pragma once
#include "Trigger.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger {
    public:
        ValueInRangeTrigger(AiManagerRegistry* const ai, const char* name, float maxValue, float minValue) : Trigger(ai, name) {
            this->maxValue = maxValue;
            this->minValue = minValue;
        }
    public: 
        virtual float GetValue() = NULL;
        virtual bool IsActive() {
            float value = GetValue();
            return value < maxValue && value > minValue;
        }

    protected:
        float maxValue, minValue;
    };

	class HealthInRangeTrigger : public ValueInRangeTrigger {
	public:
		HealthInRangeTrigger(AiManagerRegistry* const ai, const char* name, float maxValue, float minValue = 0) :
		  ValueInRangeTrigger(ai, name, maxValue, minValue) {}

		  virtual Unit* GetTarget() = NULL;
		  virtual float GetValue();
	};

    class LowHealthTrigger : public HealthInRangeTrigger {
    public:
        LowHealthTrigger(AiManagerRegistry* const ai, float value = EAT_DRINK_PERCENT, float minValue = 0) :
            HealthInRangeTrigger(ai, "low health", value, minValue) {}

		virtual Unit* GetTarget();
    };

    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger {
    public:
        PartyMemberLowHealthTrigger(AiManagerRegistry* const ai, float value = EAT_DRINK_PERCENT, float minValue = 0) :
            HealthInRangeTrigger(ai, "party member low health", value, minValue) {}
        virtual Unit* GetTarget();
    };

    class TargetLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetLowHealthTrigger(AiManagerRegistry* const ai, float value, float minValue = 0) : 
            HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual Unit* GetTarget();
    };

	class PartyMemberDeadTrigger : public Trigger {
	public:
		PartyMemberDeadTrigger(AiManagerRegistry* const ai) : Trigger(ai, "resurrect", 10) {}
		virtual bool IsActive();
	};

}