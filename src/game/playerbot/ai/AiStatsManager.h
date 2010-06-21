#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiStatsManager : public AiManagerBase
	{
	public:
		AiStatsManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

    public:
        virtual void Update();

	public:
		virtual uint8 GetHealthPercent(Unit* target);
		virtual uint8 GetRage(Unit* target);
		virtual uint8 GetEnergy(Unit* target);
		virtual uint8 GetManaPercent(Unit* target);
		virtual uint8 GetComboPoints(Player* target);
		virtual bool HasMana(Unit* target);
		virtual bool IsDead(Unit* target);
		virtual int GetAttackerCount(float distance = BOT_REACT_DISTANCE);
		virtual int GetMyAttackerCount();
        virtual float GetBalancePercent();
		virtual bool HasAggro(Unit* target);	
		virtual bool IsMounted();
		virtual void ListStats();
		virtual bool IsTank(Player* player);
		virtual bool IsDps(Player* player);

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
		uint32 EstRepair(uint16 pos);
		uint32 EstRepairAll();
        void ListBagSlots(ostringstream &out);
        void ListXP(ostringstream &out);
        void ListRepairCost(ostringstream &out);
        void ListGold(ostringstream &out);

	};

};