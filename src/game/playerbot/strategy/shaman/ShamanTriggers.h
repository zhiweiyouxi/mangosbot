#pragma once
#include "../GenericTriggers.h"

namespace ai
{
    BUFF_TRIGGER(WaterShieldTrigger, "water shield", "water shield")

    class ShamanWeaponTrigger : public BuffTrigger {
    public:
        ShamanWeaponTrigger(AiManagerRegistry* const ai) : BuffTrigger(ai, "rockbiter weapon") {}
        virtual bool IsActive();
    };

    class TotemTrigger : public BuffTrigger {
    public:
        TotemTrigger(AiManagerRegistry* const ai, const char* spell) : BuffTrigger(ai, spell) {}
        virtual bool IsActive() 
		{
            return BuffTrigger::IsActive() && statsManager->GetAttackerCount() > 2;
        }
    };

    class WindfuryTotemTrigger : public TotemTrigger {
    public:
        WindfuryTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "windfury totem") {}
    };

    class ManaSpringTotemTrigger : public TotemTrigger {
    public:
        ManaSpringTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "mana spring totem") {}
    };

    class FlametongueTotemTrigger : public TotemTrigger {
    public:
        FlametongueTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "flametongue totem") {}
    };

    class StrengthOfEarthTotemTrigger : public TotemTrigger {
    public:
        StrengthOfEarthTotemTrigger(AiManagerRegistry* const ai) : TotemTrigger(ai, "strength of earth totem") {}
    };
}