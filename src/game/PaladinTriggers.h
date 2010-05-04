#pragma once
#include "GenericTriggers.h"

namespace ai
{
	BUFF_TRIGGER(HolyShieldTrigger, "holy shield", "holy shield")
    BUFF_TRIGGER(RighteousFuryTrigger, "righteous fury", "righteous fury")

    BUFF_TRIGGER(DevotionAuraTrigger, "devotion aura", "devotion aura")
	
	class SealTrigger : public BuffTrigger
	{
	public:
		SealTrigger(PlayerbotAIFacade* const ai) : BuffTrigger(ai, "seal of justice") {}
		virtual bool IsActive();
	};

    DEBUFF_TRIGGER(JudgementOfLightTrigger, "judgement of light", "judgement of light")

    BUFF_ON_PARTY_TRIGGER(BlessingOfKingsOnPartyTrigger, "blessing of kings", "blessing of kings on party")
    BUFF_TRIGGER(BlessingTrigger, "blessing of sanctuary", "blessing of sanctuary")

}