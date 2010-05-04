#pragma once
#include "Trigger.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger {
    public:
        ValueInRangeTrigger(PlayerbotAIFacade* const ai, const char* name, float maxValue, float minValue) : Trigger(ai, name) {
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

    class LowHealthTrigger : public ValueInRangeTrigger {
    public:
        LowHealthTrigger(PlayerbotAIFacade* const ai, float value = EAT_DRINK_PERCENT, float minValue = 0) :
            ValueInRangeTrigger(ai, "low health", value, minValue) {}
        virtual float GetValue() {
          return ai->GetHealthPercent();
        }
    };

    class PartyMemberLowHealthTrigger : public ValueInRangeTrigger {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAIFacade* const ai, float value = EAT_DRINK_PERCENT, float minValue = 0) :
            ValueInRangeTrigger(ai, "party member low health", value, minValue) {}
        virtual float GetValue() {
            return ai->GetPartyMinHealthPercent();
        }
    };

    class TargetLowHealthTrigger : public ValueInRangeTrigger {
    public:
        TargetLowHealthTrigger(PlayerbotAIFacade* const ai, float value, float minValue = 0) : 
            ValueInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual float GetValue() {
            return ai->GetTargetHealthPercent();
        }
    };

}