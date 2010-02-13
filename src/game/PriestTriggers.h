#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(PowerWordFortitudeOnPartyTrigger, "power word: fortitude", "power word: fortitude on party")
    BUFF_TRIGGER(PowerWordFortitudeTrigger, "power word: fortitude", "power word: fortitude")

    BUFF_ON_PARTY_TRIGGER(DivineSpiritOnPartyTrigger, "divine spirit", "divine spirit on party")
    BUFF_TRIGGER(DivineSpiritTrigger, "divine spirit", "divine spirit")

    DEBUFF_TRIGGER(PowerWordPainTrigger, "shadow word: pain", "shadow word: pain")
}