#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BUFF_TRIGGER(DevotionAuraTrigger, "devotion aura", "devotion aura")
    BUFF_TRIGGER(SealOfJusticeTrigger, "seal of justice", "seal of justice")

    DEBUFF_TRIGGER(JudgementOfLightTrigger, "judgement of light", "judgement of light")

    BUFF_ON_PARTY_TRIGGER(BlessingOfKingsOnPartyTrigger, "blessing of kings", "blessing of kings on party")
    BUFF_TRIGGER(BlessingOfKingsTrigger, "blessing of kings", "blessing of kings")

}