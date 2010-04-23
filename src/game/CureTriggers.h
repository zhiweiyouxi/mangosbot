#pragma once
#include "Trigger.h"

namespace ai
{
    class NeedCureTrigger : public Trigger {
    public:
        NeedCureTrigger(PlayerbotAIFacade* const ai, const char* spell, uint32 dispelType, const char* name = "need cure") : Trigger(ai, name) {
            this->dispelType = dispelType;
            this->spell = spell;
        }
        virtual BOOL IsActive() {
            return ai->HasAuraToDispel(dispelType) && ai->HasSpell(spell);
        }

    protected:
        uint32 dispelType;
        const char* spell;
    };

    class TargetAuraDispelTrigger : public Trigger {
    public:
        TargetAuraDispelTrigger(PlayerbotAIFacade* const ai, const char* spell, uint32 dispelType, const char* name = "target aura dispel") : Trigger(ai, name) {
            this->dispelType = dispelType;
            this->spell = spell;
        }
        virtual BOOL IsActive() {
            return ai->TargetHasAuraToDispel(dispelType) && ai->HasSpell(spell);
        }

    protected:
        uint32 dispelType;
        const char* spell;
    };

    class PartyMemberNeedCureTrigger : public NeedCureTrigger {
    public:
        PartyMemberNeedCureTrigger(PlayerbotAIFacade* const ai, const char* spell, uint32 dispelType) : 
            NeedCureTrigger(ai, spell, dispelType, "party member need cure") {}

        virtual BOOL IsActive() {
            return ai->GetPartyMemberToDispell(dispelType) && ai->HasSpell(spell);
        }
    };
}