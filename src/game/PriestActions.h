#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_SPELL_ACTION(CastLesserHealAction, "lesser heal")
    END_SPELL_ACTION()

    class CastLesserHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "lesser heal") {}

        virtual const char* getName() { return "lesser heal on party"; }
    };

    BEGIN_SPELL_ACTION(CastFlashHealAction, "flash heal")
    END_SPELL_ACTION()

    class CastFlashHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "flash heal") {}

        virtual const char* getName() { return "flash heal on party"; }
    };

    BEGIN_SPELL_ACTION(CastHealAction, "heal")
    END_SPELL_ACTION()

    class CastHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "heal") {}

        virtual const char* getName() { return "heal on party"; }
    };

    BEGIN_SPELL_ACTION(CastRenewAction, "renew")
    END_SPELL_ACTION()

    class CastRenewOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRenewOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "renew") {}

        virtual const char* getName() { return "renew on party"; }
    };

    BEGIN_SPELL_ACTION(CastPowerWordShieldAction, "power word: shield")
    END_SPELL_ACTION()

    class CastPowerWordShieldOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastPowerWordShieldOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "power word: shield") {}

        virtual const char* getName() { return "power word: shield on party"; }
    };

    BEGIN_SPELL_ACTION(CastPowerWordFortitudeAction, "power word: fortitude")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDivineSpiritAction, "divine spirit")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastPowerWordFortitudeOnPartyAction, "power word: fortitude")
    virtual const char* getName() { return "power word: fortitude on party";}
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastDivineSpiritOnPartyAction, "divine spirit")
        virtual const char* getName() { return "divine spirit on party";}
    END_SPELL_ACTION()


    BEGIN_DEBUFF_ACTION(CastPowerWordPainAction, "shadow word: pain")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMindBlastAction, "mind blast")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCureDiseaseAction, "cure disease")
    END_SPELL_ACTION()

    class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCureDiseaseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cure disease", DISPEL_DISEASE) {}
        virtual const char* getName() { return "cure disease on party"; }
    };

    BEGIN_SPELL_ACTION(CastAbolishDiseaseAction, "abolish disease")
        virtual NextAction** getAlternatives();
    END_SPELL_ACTION()

    class CastAbolishDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishDiseaseOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "abolish disease", DISPEL_DISEASE) {}
        virtual const char* getName() { return "abolish disease on party"; }
        virtual NextAction** getAlternatives();
    };

    BEGIN_SPELL_ACTION(CastDispelMagicAction, "dispel magic")
    END_SPELL_ACTION()

    class CastDispelMagicOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastDispelMagicOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "dispel magic", DISPEL_MAGIC) {}
        virtual const char* getName() { return "dispel magic on party"; }
    };
}