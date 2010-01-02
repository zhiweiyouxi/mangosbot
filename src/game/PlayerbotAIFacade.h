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
        virtual void MoveToMaster() { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void FollowMaster() { ai->MovementClear();ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void MoveToTarget(float distance = 0.0f) { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), distance, 0); }
        virtual void Stay() {ai->MovementClear();}
        virtual void CastSpell(const char* spell, Unit* target = NULL) { ai->CastSpell(ai->getSpellId(spell), target); }
        virtual BOOL canCastSpell( const char* spell );
        virtual uint8 GetRage();
        virtual BOOL HasAura(const char* spell);
        virtual void RemoveAura(const char* spell);
        virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        virtual Player* GetPartyMinHealthPlayer();
        virtual uint8 GetPartyMinHealthPercent();
        virtual uint8 GetManaPercent() { return ai->GetManaPercent(); }
        virtual BOOL HasAggro();
        virtual int GetAttackerCount();
        
        virtual void UseHealingPotion() { FindAndUse(isHealingPotion); }
        virtual void UseManaPotion() { FindAndUse(isManaPotion); }
        virtual void UsePanicPotion()  { FindAndUse(isPanicPotion); }
        virtual void UseFood() { FindAndUse(isFood); }
        virtual void UseDrink() { FindAndUse(isDrink); }
        virtual BOOL HasHealingPotion() { return ai->FindUsableItem(isHealingPotion) != NULL; }
        virtual BOOL HasManaPotion() { return ai->FindUsableItem(isManaPotion) != NULL; }
        virtual BOOL HasPanicPotion() { return ai->FindUsableItem(isPanicPotion) != NULL; }

        // TODO: move out of this class
        static BOOL isHealingPotion(const ItemPrototype* pItemProto);
        static BOOL isManaPotion(const ItemPrototype* pItemProto);
        static BOOL isPanicPotion(const ItemPrototype* pItemProto);
        static BOOL isFood(const ItemPrototype* pItemProto);
        static BOOL isDrink(const ItemPrototype* pItemProto);
        void FindAndUse(BOOL predicate(const ItemPrototype*));

    protected:
        PlayerbotAI *ai;
    };
}