#pragma once

#include "PlayerbotAI.h"
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"

namespace ai
{
    class PlayerbotAIFacade
    {
    public:
        PlayerbotAIFacade(PlayerbotAI* const ai) { this->ai = ai; }

    public:
        virtual float GetDistanceToEnemy();
        virtual void MoveToMaster() { ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void MoveToTarget(float distance = 0.0f) { ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), distance, 0); }
        virtual void CastSpell(const char* spell) { ai->CastSpell(ai->getSpellId(spell)); }
        virtual BOOL canCastSpell( const char* spell );
        virtual uint8 GetRage();
        virtual BOOL HasAura(const char* spell);
        virtual void RemoveAura(const char* spell);
        virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        virtual uint8 GetManaPercent() { return ai->GetManaPercent(); }
        virtual BOOL HasAggro();
        virtual int GetAttackerCount() { return ai->GetAttackerCount(); }
        
        virtual void UseHealingPotion();
        virtual void UseManaPotion();
        virtual void UsePanicPotion();
        virtual BOOL HasHealingPotion() { return ai->FindUsableItem(isHealingPotion) != NULL; }
        virtual BOOL HasManaPotion() { return ai->FindUsableItem(isManaPotion) != NULL; }
        virtual BOOL HasPanicPotion() { return ai->FindUsableItem(isPanicPotion) != NULL; }

        // TODO: move out of this class
        static BOOL isHealingPotion(const ItemPrototype* pItemProto);
        static BOOL isManaPotion(const ItemPrototype* pItemProto);
        static BOOL isPanicPotion(const ItemPrototype* pItemProto);

    protected:
        PlayerbotAI *ai;
    };
}