#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_SPELL_ACTION(CastFrostNovaAction, "frost nova")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastFrostboltAction, "frostbolt")
    END_SPELL_ACTION()
    
    BEGIN_SPELL_ACTION(CastArcaneIntellectAction, "arcane intellect")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastArcaneIntellectOnPartyAction, "arcane intellect")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRemoveCurseAction, "remove curse")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastIcyVeinsAction, "icy veins")
    END_SPELL_ACTION()

    class CastRemoveCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveCurseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "remove curse", DISPEL_CURSE) {}
        virtual const char* getName() { return "remove curse on party"; }
    };
}