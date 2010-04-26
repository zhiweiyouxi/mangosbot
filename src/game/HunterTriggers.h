#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheHawkTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the hawk") {}
        virtual BOOL IsActive() {
            return !ai->HasAura(spell) && ai->canCastSpell(spell) && 
                !ai->HasAura("aspect of the viper") && ai->GetManaPercent() > 50;
        };
    };

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfTheViperTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the viper") {}
        virtual BOOL IsActive() {
            return !ai->HasAura(spell) && ai->canCastSpell(spell) && ai->GetManaPercent() < 50; 
        };
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    { 
    public: 
        HunterAspectOfThePackTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "aspect of the pack") {}
        virtual BOOL IsActive() {
            return !ai->HasAura(spell) && ai->canCastSpell(spell); 
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

}