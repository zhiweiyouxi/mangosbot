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
		virtual AiSpellManager* GetSpellManager() { return ai->GetSpellManager(); }
		virtual AiTargetManager* GetTargetManager() { return ai->GetTargetManager(); }
		virtual AiStatsManager* GetStatsManager() { return ai->GetStatsManager(); }
		virtual AiMoveManager* GetMoveManager() { return ai->GetMoveManager(); }

    public:
        //virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f);
        //virtual void MoveToMaster() { Stay(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        //virtual void FollowMaster() { Stay(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        virtual void Melee();
        virtual void Attack(Unit* target) { if (target) ai->Attack(target); }
        //virtual bool Flee(float distance = SPELL_DISTANCE);
        //virtual void GoAway(float distance = SPELL_DISTANCE);
		//virtual void MoveToTarget(float distance = 0.0f);
        //virtual void Stay();
        virtual bool HasAggro();
        virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE);
        virtual int GetMyAttackerCount();
        virtual bool IsMounted();
        //virtual bool HaveTarget() { return ai->GetCurrentTarget() != NULL; }
        virtual bool CanLoot() { return ai->CanLoot(); }
        virtual void Loot() { ai->DoLoot(); }
        virtual void TellMaster(const char* text) { ai->TellMaster(text); }

        //virtual void AttackLeastThreat();
        //virtual void AttackBiggerThreat();
        //virtual float GetFollowAngle();
        
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
        virtual float GetBalancePercent();
        //virtual bool IsTargetMoving();

		virtual bool FindAndUse(const char* item, uint8 ignore_time = 0)
		{
			return PlayerbotAIFacade::FindAndUse(isTheSameName, (const void*)item, ignore_time);
		}

    protected:
        static bool isHealingPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isManaPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isPanicPotion(const ItemPrototype* pItemProto, const void* param);
        static bool isFood(const ItemPrototype* pItemProto, const void* param);
        static bool isDrink(const ItemPrototype* pItemProto, const void* param);
		static bool isTheSameName(const ItemPrototype* pItemProto, const void* param);
        virtual bool FindAndUse(bool predicate(const ItemPrototype*, const void*), const void* param = NULL, uint8 ignore_time = 0);
        void findAllAttackers(std::list<ThreatManager*> &out);
        void findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out);

    protected:
        PlayerbotAI *ai;
    };

}