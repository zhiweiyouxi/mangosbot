#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheHawkTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the hawk") {
			checkInterval = 1;
		}
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !spellManager->HasAura("aspect of the viper", GetTarget());
        };
    };

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheViperTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the viper") {}
        virtual bool IsActive() {
			Unit* target = GetTarget();
            return !spellManager->HasAura(spell, target) && spellManager->CanCastSpell(spell, target) && ai->GetManaPercent() < 50; 
        };
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfThePackTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the pack") {}
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !spellManager->HasAura("aspect of the cheetah", GetTarget());
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

}