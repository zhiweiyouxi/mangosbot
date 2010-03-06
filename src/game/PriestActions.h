#pragma once

#include "GenericActions.h"

namespace ai
{
    class CastGreaterHealAction : public CastHealingSpellAction {
    public:
        CastGreaterHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "greater heal") {}
    };

    class CastGreaterHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastGreaterHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "greater heal") {}

        virtual const char* getName() { return "greater heal on party"; }
    };

    class CastLesserHealAction : public CastHealingSpellAction {
    public:
        CastLesserHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "lesser heal") {}
    };

    class CastLesserHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "lesser heal") {}

        virtual const char* getName() { return "lesser heal on party"; }
    };

    class CastFlashHealAction : public CastHealingSpellAction {
    public:
        CastFlashHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "flash heal") {}
    };

    class CastFlashHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "flash heal") {}

        virtual const char* getName() { return "flash heal on party"; }
    };

    class CastHealAction : public CastHealingSpellAction {
    public:
        CastHealAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "heal") {}
    };

    class CastHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "heal") {}

        virtual const char* getName() { return "heal on party"; }
    };

    class CastRenewAction : public CastHealingSpellAction {
    public:
        CastRenewAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "renew") {}
    };

    class CastRenewOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRenewOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "renew") {}

        virtual const char* getName() { return "renew on party"; }
    };

    class CastFadeAction : public CastSpellAction {
    public:
        CastFadeAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "fade") {}
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

    BEGIN_SPELL_ACTION(CastInnerFireAction, "inner fire")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyNovaAction, "holy nova")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastPowerWordFortitudeOnPartyAction, "power word: fortitude")
    virtual const char* getName() { return "power word: fortitude on party";}
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastDivineSpiritOnPartyAction, "divine spirit")
        virtual const char* getName() { return "divine spirit on party";}
    END_SPELL_ACTION()


    BEGIN_DEBUFF_ACTION(CastPowerWordPainAction, "shadow word: pain")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastDevouringPlagueAction, "devouring plague")
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