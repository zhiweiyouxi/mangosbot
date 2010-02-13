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
        virtual void MoveToMaster() { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 2.0f, GetFollowAngle()); }
        virtual void FollowMaster() { ai->MovementClear();ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 2.0f, GetFollowAngle()); }
        virtual void Melee() { ai->Attack(ai->GetCurrentTarget()); }
        virtual void Flee(float distance = SPELL_DISTANCE);
        virtual void GoAway(float distance = SPELL_DISTANCE);
        virtual void MoveToTarget(float distance = 0.0f) { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), distance, 0); }
        virtual void Stay() {ai->MovementClear();}
        virtual BOOL CastSpell(const char* spell, Unit* target = NULL) { return ai->CastSpell(ai->getSpellId(spell), target); }
        virtual BOOL canCastSpell( const char* spell );
        virtual uint8 GetRage();
        virtual BOOL HasAura(const char* spell);
        virtual BOOL PetHasAura(const char* spell);
        virtual BOOL TargetHasAura(const char* spell);
        virtual BOOL IsAllPartyHasAura(const char* spell) { return GetPartyMemberWithoutAura(spell) == NULL; }
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return findPlayer(isPlayerWithoutAura, (void*)spell); }
        virtual void RemoveAura(const char* spell);
        virtual uint8 GetComboPoints() { return ai->GetPlayerBot()->GetComboPoints(); }
        virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        virtual uint8 GetTargetHealthPercent() { return ai->GetHealthPercent(*ai->GetCurrentTarget()); }
        virtual uint8 GetPetHealthPercent() { return ai->GetHealthPercent(*ai->GetPlayerBot()->GetPet()); }
        virtual BOOL HasPet() { return ai->GetPlayerBot()->GetPet() != NULL; }
        virtual BOOL IsPetDead() { return ai->GetPlayerBot()->GetPet()->getDeathState() != ALIVE; }
        virtual Player* GetPartyMinHealthPlayer();
        virtual uint8 GetPartyMinHealthPercent();
        virtual uint8 GetManaPercent() { return ai->GetManaPercent(); }
        virtual BOOL HasAggro();
        virtual int GetAttackerCount();
        virtual int GetMyAttackerCount();
        virtual BOOL IsMounted();
        virtual BOOL HaveTarget() { return ai->GetCurrentTarget() != NULL; }
        virtual bool CanLoot() { return ai->CanLoot(); }
        virtual void Loot() { ai->DoLoot(); }
        virtual void TellMaster(const char* text) { ai->TellMaster(text); }

        virtual void AttackLeastThreat();
        virtual void AttackBiggerThreat();
        virtual float GetFollowAngle();
        
        virtual void UseHealingPotion() { FindAndUse(isHealingPotion); }
        virtual void UseManaPotion() { FindAndUse(isManaPotion); }
        virtual void UsePanicPotion()  { FindAndUse(isPanicPotion); }
        virtual void UseFood();
        virtual void UseDrink();
        virtual BOOL HasHealingPotion() { return ai->FindUsableItem(isHealingPotion) != NULL; }
        virtual BOOL HasManaPotion() { return ai->FindUsableItem(isManaPotion) != NULL; }
        virtual BOOL HasPanicPotion() { return ai->FindUsableItem(isPanicPotion) != NULL; }

        virtual void Emote(uint32 emote);

    protected:
        static BOOL isHealingPotion(const ItemPrototype* pItemProto);
        static BOOL isManaPotion(const ItemPrototype* pItemProto);
        static BOOL isPanicPotion(const ItemPrototype* pItemProto);
        static BOOL isFood(const ItemPrototype* pItemProto);
        static BOOL isDrink(const ItemPrototype* pItemProto);
        BOOL FindAndUse(BOOL predicate(const ItemPrototype*), uint8 ignore_time = 0);
        Player* findPlayer(BOOL predicate(Player*, FindPlayerParam&), void *param);
        static BOOL isPlayerWithoutAura(Player* player, FindPlayerParam &param /*const char* spell*/);
        void findAllAttackers(std::list<ThreatManager*> &out);
        void findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out);

    protected:
        PlayerbotAI *ai;
    };

}