#ifndef _PLAYERBOTMGR_H
#define _PLAYERBOTMGR_H

#include "Common.h"
#include "AiGroupStatsManager.h"
#include "PlayerbotAIBase.h"

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;
class PlayerbotClassAI;

typedef UNORDERED_MAP<uint64, Player*> PlayerBotMap;

class MANGOS_DLL_SPEC PlayerbotMgr : public PlayerbotAIBase
{
    public:
        PlayerbotMgr(Player* const master);
        virtual ~PlayerbotMgr();

        void UpdateAI(uint32 elapsed);
        void HandleMasterIncomingPacket(const WorldPacket& packet);
        void HandleMasterOutgoingPacket(const WorldPacket& packet);

        void AddPlayerBot(uint64 guid, WorldSession* session);
        void LogoutPlayerBot(uint64 guid);
        Player* GetPlayerBot (uint64 guid) const;
        Player* GetMaster() const { return m_master; };
        PlayerBotMap::const_iterator GetPlayerBotsBegin() const { return m_playerBots.begin(); }
        PlayerBotMap::const_iterator GetPlayerBotsEnd()   const { return m_playerBots.end();   }

        void LogoutAllBots();
        void OnBotLogin(Player * const bot);

        ai::AiGroupStatsManager* GetGroupStatsManager() { return groupStatsManager; }

    public:
        // config variables
		bool m_confDisableBots;
        bool m_confDebugWhisper;
        float m_confFollowDistance[2];

    private:
        Player* const m_master;
        PlayerBotMap m_playerBots;     
        ai::AiGroupStatsManager *groupStatsManager;
};

#endif
