#pragma once
using namespace std;

namespace ai 
{
	class AiManagerRegistry;
    class AiManagerBase;
    class FindTargetStrategy;

	typedef bool (AiTargetManager::*FindPlayerPredicate)(Unit*, void*);
	typedef bool (AiTargetManager::*SpellEntryPredicate)(SpellEntry const*);

	class AiTargetManager : public AiManagerBase
	{
	public:
		AiTargetManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
            selection = NULL;
		}

	public:
		virtual Unit* GetPartyMemberWithoutAura(const char* spell);
		virtual Unit* GetPartyMinHealthPlayer();
		virtual Unit* GetDeadPartyMember();
		virtual Unit* GetPartyMemberToDispell(uint32 dispelType);
		virtual Unit* FindTargetForTank();
		virtual Unit* FindTargetForDps();
        virtual Unit* GetCurrentTarget() { return selection; }
        virtual void SetCurrentTarget(Unit* target) { selection = target; }
		virtual Player* GetSelf();
		virtual Unit* GetPet();
		virtual Player* GetMaster();
        virtual void ResetTarget() { selection = NULL; }

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
		Unit* FindPartyMember(FindPlayerPredicate predicate, void *param);
		bool CheckPredicate(Unit* player, FindPlayerPredicate predicate, void *param);
		bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate predicate);
		bool IsTargetOfHealingSpell(Player* target);
		bool IsTargetOfResurrectSpell(Player* target);
		virtual bool HasAuraToDispel(uint32 dispelType) { return HasAuraToDispel(bot, dispelType); }
		bool HasAuraToDispel(Unit* player, uint32 dispelType);
		bool canDispel(const SpellEntry* entry, uint32 dispelType);

	private:
		bool IsHealingSpell(SpellEntry const* spell);
		bool IsResurrectSpell(SpellEntry const* spell);
		bool CanHealPet(Pet* pet);

	private:
		Unit* FindTarget(FindTargetStrategy* strategy);

	private:
		bool PlayerWithoutAuraPredicate(Unit* player, void *param /*const char* spell*/);

    private:
        Unit* selection;

	};

};