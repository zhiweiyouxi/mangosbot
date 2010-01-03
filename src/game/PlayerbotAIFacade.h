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
    struct FindPlayerParam
    {
        PlayerbotAI *ai;
        void* param;
    };

    class PlayerbotAIFacade
    {
    public:
        PlayerbotAIFacade(PlayerbotAI* const ai) { this->ai = ai; }

    public:
        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f);
        virtual void MoveToMaster() { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void FollowMaster() { ai->MovementClear();ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void Flee(float distance = SPELL_DISTANCE);
        virtual void MoveToTarget(float distance = 0.0f) { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), distance, 0); }
        virtual void Stay() {ai->MovementClear();}
        virtual void CastSpell(const char* spell, Unit* target = NULL) { ai->CastSpell(ai->getSpellId(spell), target); }
        virtual BOOL canCastSpell( const char* spell );
        virtual uint8 GetRage();
        virtual BOOL HasAura(const char* spell);
        virtual BOOL TargetHasAura(const char* spell);
        virtual BOOL IsAllPartyHasAura(const char* spell) { return GetPartyMemberWithoutAura(spell) == NULL; }
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return findPlayer(isPlayerWithoutAura, (void*)spell); }
        virtual void RemoveAura(const char* spell);
        virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        virtual uint8 GetTargetHealthPercent() { return ai->GetHealthPercent(*ai->GetCurrentTarget()); }
        virtual Player* GetPartyMinHealthPlayer();
        virtual uint8 GetPartyMinHealthPercent();
        virtual uint8 GetManaPercent() { return ai->GetManaPercent(); }
        virtual BOOL HasAggro();
        virtual int GetAttackerCount();

        virtual void AttackLeastThreat();
        virtual void AttackBiggerThreat();
        
        virtual void UseHealingPotion() { FindAndUse(isHealingPotion); }
        virtual void UseManaPotion() { FindAndUse(isManaPotion); }
        virtual void UsePanicPotion()  { FindAndUse(isPanicPotion); }
        virtual void UseFood() { FindAndUse(isFood); ai->SetIgnoreUpdateTime(30); }
        virtual void UseDrink() { FindAndUse(isDrink); ai->SetIgnoreUpdateTime(30); }
        virtual BOOL HasHealingPotion() { return ai->FindUsableItem(isHealingPotion) != NULL; }
        virtual BOOL HasManaPotion() { return ai->FindUsableItem(isManaPotion) != NULL; }
        virtual BOOL HasPanicPotion() { return ai->FindUsableItem(isPanicPotion) != NULL; }

    protected:
        static BOOL isHealingPotion(const ItemPrototype* pItemProto);
        static BOOL isManaPotion(const ItemPrototype* pItemProto);
        static BOOL isPanicPotion(const ItemPrototype* pItemProto);
        static BOOL isFood(const ItemPrototype* pItemProto);
        static BOOL isDrink(const ItemPrototype* pItemProto);
        void FindAndUse(BOOL predicate(const ItemPrototype*));
        Player* findPlayer(BOOL predicate(Player*, FindPlayerParam&), void *param);
        static BOOL isPlayerWithoutAura(Player* player, FindPlayerParam &param /*const char* spell*/);
        void findAllAttackers(std::list<ThreatManager*> &out);
        void findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out);

    protected:
        PlayerbotAI *ai;
    };

}