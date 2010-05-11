#ifndef _PLAYERBOTAI_H
#define _PLAYERBOTAI_H

#include "Common.h"
#include "QuestDef.h"

using namespace std;


class WorldPacket;
class WorldObject;
class Player;
class Unit;
class Object;
class Item;
class PlayerbotClassAI;
class PlayerbotMgr;

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f

class MANGOS_DLL_SPEC PlayerbotAI
{
    public:
        enum ScenarioType
        {
            SCENARIO_PVEEASY,
            SCENARIO_PVEHARD,
            SCENARIO_DUEL,
            SCENARIO_PVPEASY,
            SCENARIO_PVPHARD
        };

		enum CombatStyle {
			COMBAT_MELEE		= 0x01,		// class melee attacker
			COMBAT_RANGED		= 0x02		// class is ranged attacker
		};

        // masters orders that should be obeyed by the AI during the updteAI routine
        // the master will auto set the target of the bot
        enum CombatOrderType
        {
            ORDERS_NONE			= 0x00,		// no special orders given
			ORDERS_TANK			= 0x01,		// bind attackers by gaining threat
			ORDERS_ASSIST		= 0x02,		// assist someone (dps type)
			ORDERS_HEAL			= 0x04,		// concentrate on healing (no attacks, only self defense)
			ORDERS_PROTECT		= 0x10,		// combinable state: check if protectee is attacked
			ORDERS_PRIMARY		= 0x0F,
			ORDERS_SECONDARY	= 0xF0,
			ORDERS_RESET		= 0xFF
        };

        enum CombatTargetType
        {
            TARGET_NORMAL       = 0x00,
            TARGET_THREATEN     = 0x01     
        };

        enum BotState
        {
            BOTSTATE_NORMAL,        // normal AI routines are processed
            BOTSTATE_COMBAT,        // bot is in combat
            BOTSTATE_DEAD,          // we are dead and wait for becoming ghost
            BOTSTATE_DEADRELEASED,  // we released as ghost and wait to revive
            BOTSTATE_LOOTING        // looting mode, used just after combat
        };

		enum MovementOrderType 
		{
			MOVEMENT_NONE		= 0x00,
			MOVEMENT_FOLLOW		= 0x01,
			MOVEMENT_STAY		= 0x02
		};

        typedef std::map<uint32, uint32> BotNeedItem;
        typedef std::list<uint64> BotLootCreature;

        // attacker query used in PlayerbotAI::FindAttacker()
        enum ATTACKERINFOTYPE
        {
            AIT_NONE            = 0x00,
            AIT_LOWESTTHREAT    = 0x01,
            AIT_HIGHESTTHREAT   = 0x02,
            AIT_VICTIMSELF      = 0x04,
            AIT_VICTIMNOTSELF   = 0x08		// !!! must use victim param in FindAttackers
        };
        struct AttackerInfo
        {
            Unit*    attacker;        // reference to the attacker
            Unit*    victim;          // combatant's current victim
            float    threat;          // own threat on this combatant
            float    threat2;         // highest threat not caused by bot
            uint32  count;            // number of units attacking
            uint32  source;           // 1=bot, 2=master, 3=group
        };
        typedef std::map<uint64,AttackerInfo> AttackerInfoList;

    public:
        PlayerbotAI(PlayerbotMgr* const mgr, Player* const bot);
        PlayerbotAI() : m_mgr(NULL), m_bot(NULL) {} // for mocking purpose
        virtual ~PlayerbotAI();

        // This is called from Unit.cpp and is called every second (I think)
        void UpdateAI(const uint32 p_time);

        // This is called from ChatHandler.cpp when there is an incoming message to the bot
        // from a whisper or from the party channel
        void HandleCommand(const std::string& text, Player& fromPlayer);

        // This is called by WorldSession.cpp
        // It provides a view of packets normally sent to the client.
        // Since there is no client at the other end, the packets are dropped of course.
        // For a list of opcodes that can be caught see Opcodes.cpp (SMSG_* opcodes only)
        void HandleBotOutgoingPacket(const WorldPacket& packet);

        // This is called by WorldSession.cpp
        // when it detects that a bot is being teleported. It acknowledges to the server to complete the
        // teleportation
        void HandleTeleportAck();

        // Returns what kind of situation we are in so the ai can react accordingly
        ScenarioType GetScenarioType() {return m_ScenarioType;}

        PlayerbotClassAI* GetClassAI() {return m_classAI;}
        PlayerbotMgr* const GetManager() {return m_mgr;}

        // finds spell ID for matching substring args
        // in priority of full text match, spells not taking reagents, and highest rank
        virtual uint32 findSpellId(const char* args, bool master = false);
		virtual uint32 getSpellId(const char* args, bool master = false);

        // extracts item ids from links
        void extractItemIds(const std::string& text, std::list<uint32>& itemIds) const;

        // extracts currency from a string as #g#s#c and returns the total in copper
        uint32 extractMoney(const std::string& text) const;

        // finds items in bots equipment and adds them to foundItemList, removes found items from itemIdSearchList
        void findItemsInEquip(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList) const;
        // finds items in bots inventory and adds them to foundItemList, removes found items from itemIdSearchList
        void findItemsInInv(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList) const;

        // currently bots only obey commands from the master
        bool canObeyCommandFrom(const Player& player) const;

        // get current casting spell (will return NULL if no spell!)
        Spell* GetCurrentSpell() const;

        bool HasAura(uint32 spellId, const Unit& player);
        bool HasAura(const char* spellName, const Unit& player);
        bool HasAura(const char* spellName);

        uint8 GetHealthPercent(const Unit& target) const;
        uint8 GetHealthPercent() const;
        uint8 GetBaseManaPercent(const Unit& target) const;
        uint8 GetBaseManaPercent() const;
        uint8 GetManaPercent(const Unit& target) const;
        uint8 GetManaPercent() const;
        uint8 GetRageAmount(const Unit& target) const;
        uint8 GetRageAmount() const;
        uint8 GetRagePercent(const Unit& target) const;
        uint8 GetRagePercent() const;
        uint8 GetEnergyAmount(const Unit& target) const;
        uint8 GetEnergyAmount() const;
        uint8 GetRunicPower(const Unit& target) const;
        uint8 GetRunicPower() const;

        Item* FindFood() { return FindUsableItem(isFood); }
        static bool isFood(const ItemPrototype* pItemProto, const void* param);
        Item* FindDrink() const { return FindUsableItem(isDrink); }
        static bool isDrink(const ItemPrototype* pItemProto, const void* param);
        Item* FindBandage() { return FindUsableItem(isBandage); }
        static bool isBandage(const ItemPrototype* pItemProto, const void* param);
        Item* FindPoison() { return FindUsableItem(isPoison); }
        static bool isPoison(const ItemPrototype* pItemProto, const void* param);


		Item* FindUsableItem(bool predicate(const ItemPrototype*, const void*), const void* param = NULL, int* count = NULL) const;
        Item* FindMount(uint32 matchingRidingSkill) const;


        // ******* Actions ****************************************
        // Your handlers can call these actions to make the bot do things.
        void TellMaster(const std::string& text) const;
        void TellMaster( const char *fmt, ... ) const;
        void SendWhisper(const std::string& text, Player& player) const;
        bool CastSpell(const char* args);
        bool CastSpell(uint32 spellId);
        bool CastSpell(uint32 spellId, Unit& target);
        bool CastSpell(uint32 spellId, Unit* target)
        {
            return target ? CastSpell(spellId, *target) : CastSpell(spellId);
        }
		int UpdateIgnoreTime(uint32 spellId);

        void UseItem(Item& item);
        void EquipItem(Item& item);
        //void Stay();
        //bool Follow(Player& player);
        void SendNotEquipList(Player& player);
        void Feast();
        void InterruptCurrentCastingSpell();
        void GetCombatTarget( Unit* forcedTarged = 0 );
        Unit *GetCurrentTarget() { return m_targetCombat; };
        void DoNextCombatManeuver();
		void DoCombatMovement();
        void SetIgnoreUpdateTime(uint8 t) {m_ignoreAIUpdatesUntilTime=time(0) + t; };

        Player *GetPlayerBot() const {return m_bot;}
        Player *GetPlayer() const {return m_bot;}
        Player *GetMaster() const;

        BotState GetState() { return m_botState; };
        void SetState( BotState state );
        void SetQuestNeedItems();
        void SendQuestItemList( Player& player );
		void SendOrders( Player& player );
        bool FollowCheckTeleport( WorldObject &obj );
        void DoLoot();
        bool CanLoot() { return !m_lootCreature.empty(); }

        void AcceptQuest( Quest const *qInfo, Player *pGiver );
        void TurnInQuests( WorldObject *questgiver );

        bool IsInCombat();
        void UpdateAttackerInfo();
        Unit* FindAttacker( ATTACKERINFOTYPE ait=AIT_NONE, Unit *victim=0 );
        uint32 GetAttackerCount() { return m_attackerInfo.size(); };
		void SetCombatOrderByStr( std::string str, Unit *target=0 );
		void SetCombatOrder( CombatOrderType co, Unit *target=0 );
		CombatOrderType GetCombatOrder() { return this->m_combatOrder; }
		void SetMovementOrder( MovementOrderType mo, Unit *followTarget=0 );
		MovementOrderType GetMovementOrder() { return this->m_movementOrder; }
		void MovementReset();
		void MovementUpdate();
		void MovementClear();
		bool IsMoving();
		void Drink();
		void Eat();
		void Bandage();
		void UseLongTimeItem(Item* pItem, uint8 time = 30);
        void SetInFront( const Unit* obj );
        void Attack(Unit* thingToAttack);
		void Revive();

        void ItemLocalization(std::string& itemName, const uint32 itemID) const;
        void QuestLocalization(std::string& questTitle, const uint32 questID) const;

    private:
        // ****** Closed Actions ********************************
        // These actions may only be called at special times.
        // Trade methods are only applicable when the trade window is open
        // and are only called from within HandleCommand.
        bool TradeItem(const Item& item, int8 slot=-1);
        bool TradeCopper(uint32 copper);

        // it is safe to keep these back reference pointers because m_bot
        // owns the "this" object and m_master owns m_bot. The owner always cleans up.
        PlayerbotMgr* const m_mgr;
        Player* const m_bot;
        PlayerbotClassAI* m_classAI;

        // ignores AI updates until time specified
        // no need to waste CPU cycles during casting etc
        time_t m_ignoreAIUpdatesUntilTime;

		CombatStyle m_combatStyle;
        CombatOrderType m_combatOrder;
		MovementOrderType m_movementOrder;

        ScenarioType m_ScenarioType;

        // defines the state of behaviour of the bot
        BotState m_botState;

        // list of items needed to fullfill quests
        BotNeedItem m_needItemList;

        // list of creatures we recently attacked and want to loot
        BotLootCreature m_lootCreature;  // list of creatures
        uint64 m_lootCurrent;            // current remains of interest

        time_t m_TimeDoneEating;
        time_t m_TimeDoneDrinking;
        uint32 m_CurrentlyCastingSpellId;
        //bool m_IsFollowingMaster;

        // if master commands bot to do something, store here until updateAI
        // can do it
        uint32 m_spellIdCommand;
        uint64 m_targetGuidCommand;

        AttackerInfoList m_attackerInfo;

        bool m_targetChanged;
        CombatTargetType m_targetType;

		Unit *m_targetCombat;	// current combat target
		Unit *m_targetAssist;	// get new target by checking attacker list of assisted player
		Unit *m_targetProtect;	// check 

		Unit *m_followTarget;	// whom to follow in non combat situation?

		std::map<std::string, uint32> spellMap;

};

#endif
