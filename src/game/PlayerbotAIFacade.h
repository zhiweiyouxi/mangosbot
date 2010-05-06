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
        virtual void MoveToMaster() { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        virtual void FollowMaster() { ai->MovementClear();ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        virtual void Melee() { ai->Attack(ai->GetCurrentTarget()); }
        virtual void Flee(float distance = SPELL_DISTANCE);
        virtual void GoAway(float distance = SPELL_DISTANCE);
        virtual void MoveToTarget(float distance = 0.0f) { ai->MovementClear(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), distance, 0); }
        virtual void Stay() {ai->MovementClear();}
        virtual bool CastSpellOnCurrentTarget(const char* spell) { return ai->CastSpell(ai->getSpellId(spell), ai->GetCurrentTarget()); }
        virtual bool CastSpell(const char* spell, Unit* target = NULL) { return ai->CastSpell(ai->getSpellId(spell), target); }
        virtual bool canCastSpell( const char* spell );
        virtual uint8 GetRage();
        virtual bool HasAura(const char* spell);
		virtual bool HasAnyAuraOf(const char* first, ...);
        virtual bool PetHasAura(const char* spell);
        virtual bool TargetHasAura(const char* spell);
        virtual bool IsAllPartyHasAura(const char* spell) { return GetPartyMemberWithoutAura(spell) == NULL; }
        virtual Player* GetPartyMemberWithoutAura(const char* spell) { return findPlayer(isPlayerWithoutAura, (void*)spell); }
        virtual void RemoveAura(const char* spell);
        virtual uint8 GetComboPoints() { return ai->GetPlayerBot()->GetComboPoints(); }
        virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        virtual uint8 GetTargetHealthPercent() { return ai->GetHealthPercent(*ai->GetCurrentTarget()); }
        virtual uint8 GetPetHealthPercent() { return ai->GetHealthPercent(*ai->GetPlayerBot()->GetPet()); }
        virtual bool HasPet() { return ai->GetPlayerBot()->GetPet() != NULL; }
        virtual bool IsPetDead() { return ai->GetPlayerBot()->GetPet()->getDeathState() != ALIVE; }
        virtual Player* GetPartyMinHealthPlayer();
        virtual uint8 GetPartyMinHealthPercent();
        virtual uint8 GetManaPercent() { return ai->GetManaPercent(); }
        virtual bool HasAggro();
        virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE);
        virtual int GetMyAttackerCount();
        virtual bool IsMounted();
        virtual bool HaveTarget() { return ai->GetCurrentTarget() != NULL; }
        virtual bool CanLoot() { return ai->CanLoot(); }
        virtual void Loot() { ai->DoLoot(); }
        virtual void TellMaster(const char* text) { ai->TellMaster(text); }
        virtual bool HasSpell(const char* spell) { return ai->getSpellId(spell) > 0; }

        virtual void AttackLeastThreat();
        virtual void AttackBiggerThreat();
        virtual float GetFollowAngle();
        
        virtual void UseHealingPotion() { FindAndUse(isHealingPotion); }
        virtual void UseManaPotion() { FindAndUse(isManaPotion); }
        virtual void UsePanicPotion()  { FindAndUse(isPanicPotion); }
        virtual void UseFood();
        virtual void UseDrink();
        virtual bool HasFood() { return ai->FindUsableItem(isFood) != NULL; }
        virtual bool HasDrink() { return ai->FindUsableItem(isDrink) != NULL; }
        virtual bool HasHealingPotion() { return ai->FindUsableItem(isHealingPotion) != NULL; }
        virtual bool HasManaPotion() { return ai->FindUsableItem(isManaPotion) != NULL; }
        virtual bool HasPanicPotion() { return ai->FindUsableItem(isPanicPotion) != NULL; }
		virtual int GetItemCount(const char* name) { return ai->FindUsableItem(isTheSameName, (const void*)name) != NULL; }

        virtual void Emote(uint32 emote);
        virtual Player* GetPartyMemberToDispell(uint32 dispelType);
        virtual bool HasAuraToDispel(uint32 dispelType) { return HasAuraToDispel(ai->GetPlayerBot(), dispelType); }
        virtual float GetBalancePercent();
        virtual bool IsTargetMoving();
        virtual bool IsTargetCastingNonMeleeSpell();
        virtual bool TargetHasAuraToDispel(uint32 dispelType);

    protected:
        static bool isHealingPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isManaPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isPanicPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isFood(const ItemPrototype* pItemProto, const void* param);
        static bool isDrink(const ItemPrototype* pItemProto, const void* param);
		static bool isTheSameName(const ItemPrototype* pItemProto, const void* param);
        bool FindAndUse(bool predicate(const ItemPrototype*, const void*), uint8 ignore_time = 0);
        Player* findPlayer(bool predicate(Player*, FindPlayerParam&), void *param);
        static bool isPlayerWithoutAura(Player* player, FindPlayerParam &param /*const char* spell*/);
        void findAllAttackers(std::list<ThreatManager*> &out);
        void findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out);
        bool HasAuraToDispel(Unit* player, uint32 dispelType);

    protected:
        PlayerbotAI *ai;
    };

}