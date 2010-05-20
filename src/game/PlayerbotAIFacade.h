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


    public:
        virtual float GetDistanceToEnemy(float ifNoTarget = 0.0f);
        virtual void MoveToMaster() { Stay(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        virtual void FollowMaster() { Stay(); ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 1.5f, GetFollowAngle()); }
        virtual void Melee();
        virtual bool Flee(float distance = SPELL_DISTANCE);
        virtual void GoAway(float distance = SPELL_DISTANCE);
		virtual void MoveToTarget(float distance = 0.0f);
        virtual void Stay();
        //virtual bool CastSpellOnCurrentTarget(const char* spell) { return CastSpell(spell, ai->GetCurrentTarget()); }
        //virtual bool CastSpell(const char* spell, Unit* target = NULL, bool checkAura = true);
        //virtual bool canCastSpell( const char* spell );
        virtual uint8 GetRage();
		virtual uint8 GetEnergy();
        //virtual bool HasAura(const char* spell);
		//virtual bool HasAnyAuraOf(const char* first, ...);
        //virtual bool PetHasAura(const char* spell);
        //virtual bool TargetHasAura(const char* spell);
        //virtual bool IsAllPartyHasAura(const char* spell) { return GetPartyMemberWithoutAura(spell) == NULL; }
        //virtual Unit* GetPartyMemberWithoutAura(const char* spell) { return findPlayer(isPlayerWithoutAura, (void*)spell); }
        //virtual void RemoveAura(const char* spell);
        virtual uint8 GetComboPoints() { return ai->GetPlayerBot()->GetComboPoints(); }
        //virtual uint8 GetHealthPercent() { return ai->GetHealthPercent(); }
        //virtual uint8 GetTargetHealthPercent() { return ai->GetHealthPercent(*ai->GetCurrentTarget()); }
		virtual uint8 GetTargetManaPercent() { return ai->GetManaPercent(*ai->GetCurrentTarget()); }
        virtual uint8 GetPetHealthPercent() { return ai->GetHealthPercent(*ai->GetPlayerBot()->GetPet()); }
        virtual bool HasPet() { return ai->GetPlayerBot()->GetPet() != NULL; }
        virtual bool IsPetDead() { return ai->GetPlayerBot()->GetPet()->getDeathState() != ALIVE; }
        //virtual Unit* GetPartyMinHealthPlayer();
		//virtual Unit* GetDeadPartyMember();
        //virtual uint8 GetPartyMinHealthPercent();
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
        //virtual Unit* GetPartyMemberToDispell(uint32 dispelType);
        //virtual bool HasAuraToDispel(uint32 dispelType) { return HasAuraToDispel(ai->GetPlayerBot(), dispelType); }
        virtual float GetBalancePercent();
        virtual bool IsTargetMoving();
        //virtual bool IsTargetCastingNonMeleeSpell();
        //virtual bool TargetHasAuraToDispel(uint32 dispelType);
        //virtual bool IsTargetOfSpellCast(Player* target, bool predicate(SpellEntry const*));
        //virtual bool IsTargetOfHealingSpell(Player* target);
        //virtual bool IsTargetOfResurrectSpell(Player* target);


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
        Unit* findPlayer(bool predicate(Unit*, FindPlayerParam*), void *param);
        static bool isPlayerWithoutAura(Unit* player, FindPlayerParam *param /*const char* spell*/);
        void findAllAttackers(std::list<ThreatManager*> &out);
        void findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out);
        //bool HasAuraToDispel(Unit* player, uint32 dispelType);
		bool checkPredicate(Unit* player, bool predicate(Unit*, FindPlayerParam*), FindPlayerParam *param);

    protected:
        PlayerbotAI *ai;
    };

}