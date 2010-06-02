#include "Config/ConfigEnv.h"
#include "Player.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "WorldPacket.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "GossipDef.h"
#include "Chat.h"
#include "Language.h"
#include "Group.h"
#include "Guild.h"
#include "AiManagerRegistry.h"
#include "AiSocialManager.h"
#include "AiQuestManager.h"

class LoginQueryHolder;
class CharacterHandler;


PlayerbotMgr::PlayerbotMgr(Player* const master) : PlayerbotAIBase(),  m_master(master) 
{
    // load config variables
	m_confDisableBots = sConfig.GetBoolDefault( "PlayerbotAI.DisableBots", false );
    m_confDebugWhisper = sConfig.GetBoolDefault( "PlayerbotAI.DebugWhisper", false );
    m_confFollowDistance[0] = sConfig.GetFloatDefault( "PlayerbotAI.FollowDistanceMin", 0.5f );
    m_confFollowDistance[1] = sConfig.GetFloatDefault( "PlayerbotAI.FollowDistanceMin", 1.0f );

    groupStatsManager = new ai::AiGroupStatsManager(master);
}

PlayerbotMgr::~PlayerbotMgr() 
{
    LogoutAllBots();
    if (groupStatsManager)
        delete groupStatsManager;
}

void PlayerbotMgr::UpdateAI(const uint32 p_time) 
{
    if (!CanUpdateAI())
        return;

    SetNextCheckDelay(GLOBAL_COOLDOWN);

    groupStatsManager->Update();
}

void PlayerbotMgr::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
        // if master is logging out, log out all bots
        case CMSG_LOGOUT_REQUEST:
        {
            LogoutAllBots();
            return;
        }

        // If master inspects one of his bots, give the master useful info in chat window
        // such as inventory that can be equipped
        case CMSG_INSPECT:
        {
            WorldPacket p(packet);
            p.rpos(0); // reset reader
            uint64 guid;
            p >> guid;
            Player* const bot = GetPlayerBot(guid);
            //if (bot) bot->GetPlayerbotAI()->SendNotEquipList(*bot);
            return;
        }

        case CMSG_GAMEOBJ_USE:
            {
                WorldPacket p(packet);
        	    p.rpos(0); // reset reader
        	    uint64 objGUID;
        	    p >> objGUID;

                GameObject *obj = m_master->GetMap()->GetGameObject( objGUID );
                if( !obj )
                    return;

            	for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
            	{
            		Player* const bot = it->second;

                    if( obj->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER )
                    {
                        bot->GetPlayerbotAI()->GetAiRegistry()->GetQuestManager()->TurnInQuests( obj );
                    }
                    // add other go types here, i.e.:
                    // GAMEOBJECT_TYPE_CHEST - loot quest items of chest
                }
            }
            break;

        // if master talks to an NPC
        case CMSG_GOSSIP_HELLO:
        case CMSG_QUESTGIVER_HELLO:
        {
        	WorldPacket p(packet);
        	p.rpos(0); // reset reader
        	uint64 npcGUID;
        	p >> npcGUID;
        	
        	WorldObject* pNpc = m_master->GetMap()->GetWorldObject( npcGUID );
        	if (!pNpc)
        		return;

        	// for all master's bots
        	for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
        	{
        		Player* const bot = it->second;
                bot->GetPlayerbotAI()->GetAiRegistry()->GetQuestManager()->TurnInQuests( pNpc );
        	}
        	        
        	return;
        }

        // if master accepts a quest, bots should also try to accept quest
        case CMSG_QUESTGIVER_ACCEPT_QUEST:
        {
            WorldPacket p(packet);
            p.rpos(0); // reset reader
            uint64 guid;
            uint32 quest;
            p >> guid >> quest;
            Quest const* qInfo = sObjectMgr.GetQuestTemplate(quest);
            if (qInfo)
            {
                for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
                {
                    Player* const bot = it->second;
                    
                    if (bot->GetQuestStatus(quest) == QUEST_STATUS_COMPLETE)
						bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I already completed that quest.");
                    else if (! bot->CanTakeQuest(qInfo, false))
                    {                    	
        				if (! bot->SatisfyQuestStatus(qInfo, false))
                            bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I already have that quest.");
                        else
                            bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I can't take that quest.");
                    }
                    else if (! bot->SatisfyQuestLog(false))
                        bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("My quest log is full.");
                    else if (! bot->CanAddQuest(qInfo, false))
                        bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("I can't take that quest because it requires that I take items, but my bags are full!");

                    else
                    {
                        p.rpos(0); // reset reader
                        bot->GetSession()->HandleQuestgiverAcceptQuestOpcode(p);
                        bot->GetPlayerbotAI()->GetAiRegistry()->GetSocialManager()->TellMaster("Got the quest.");
                    }
                }
            }
            return;
        }
		case CMSG_LOOT_ROLL:
		{

			WorldPacket p(packet); //WorldPacket packet for CMSG_LOOT_ROLL, (8+4+1)
			uint64 Guid;
			uint32 NumberOfPlayers;
			uint8 rollType;
			p.rpos(0); //reset packet pointer
			p >> Guid; //guid of the item rolled
			p >> NumberOfPlayers; //number of players invited to roll
			p >> rollType; //need,greed or pass on roll


			for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
				{

					uint32 choice = urand(0,2); //returns 0,1,or 2

					Player* const bot = it->second;
					if(!bot)
						return;

					Group* group = bot->GetGroup();
					if(!group)
						return;

					switch (group->GetLootMethod())
						{
						case GROUP_LOOT:
							// bot random roll
							group->CountRollVote(bot->GetGUID(), Guid, NumberOfPlayers, choice);
							break;
						case NEED_BEFORE_GREED:
							choice = 1;
							// bot need roll
							group->CountRollVote(bot->GetGUID(), Guid, NumberOfPlayers, choice);
							break;
						case MASTER_LOOT:
							choice = 0;
							// bot pass on roll
							group->CountRollVote(bot->GetGUID(), Guid, NumberOfPlayers, choice);
							break;
						default:
							break;
						}

					switch (rollType)
						{
						case ROLL_NEED:
							bot->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED, 1);
							break;
						case ROLL_GREED:
							bot->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED, 1);
							break;
						}

				}
		return;
		}

		case CMSG_REPAIR_ITEM:
			{

				WorldPacket p(packet); // WorldPacket packet for CMSG_REPAIR_ITEM, (8+8+1)

				sLog.outDebug("PlayerbotMgr: CMSG_REPAIR_ITEM");

				uint64 npcGUID, itemGUID;
				uint8 guildBank;

				p.rpos(0); //reset packet pointer
				p >> npcGUID;
				p >> itemGUID;  // Not used for bot but necessary opcode data retrieval
				p >> guildBank; // Flagged if guild repair selected

				for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
				{

					Player* const bot = it->second;
					if(!bot)
						return;

					Group* group = bot->GetGroup();  // check if bot is a member of group
					if(!group)
						return;

					Creature *unit = bot->GetNPCIfCanInteractWith(npcGUID, UNIT_NPC_FLAG_REPAIR);
					if (!unit) // Check if NPC can repair bot or not
					{
						sLog.outDebug("PlayerbotMgr: HandleRepairItemOpcode - Unit (GUID: %u) not found or you can't interact with him.", uint32(GUID_LOPART(npcGUID)));
						return;
					}

					// remove fake death
					if(bot->hasUnitState(UNIT_STAT_DIED))
						bot->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH);

					// reputation discount
					float discountMod = bot->GetReputationPriceDiscount(unit);

					uint32 TotalCost = 0;
					if (itemGUID) // Handle redundant feature (repair individual item) for bot
					{
						sLog.outDebug("ITEM: Repair single item is not applicable for %s",bot->GetName());
						continue;
					}
					else  // Handle feature (repair all items) for bot
					{
						sLog.outDebug("ITEM: Repair all items, npcGUID = %u", GUID_LOPART(npcGUID));

						TotalCost = bot->DurabilityRepairAll(true,discountMod,guildBank>0?true:false);
					}
					if (guildBank) // Handle guild repair
					{
						uint32 GuildId = bot->GetGuildId();
						if (!GuildId)
							return;
						Guild *pGuild = sObjectMgr.GetGuildById(GuildId);
						if (!pGuild)
							return;
						pGuild->LogBankEvent(GUILD_BANK_LOG_REPAIR_MONEY, 0, bot->GetGUIDLow(), TotalCost);
						pGuild->SendMoneyInfo(bot->GetSession(), bot->GetGUIDLow());
					}

				}
				return;
			}

        /*
        case CMSG_NAME_QUERY:
        case MSG_MOVE_START_FORWARD:
        case MSG_MOVE_STOP:
        case MSG_MOVE_SET_FACING:
        case MSG_MOVE_START_STRAFE_LEFT:
        case MSG_MOVE_START_STRAFE_RIGHT:
        case MSG_MOVE_STOP_STRAFE:
        case MSG_MOVE_START_BACKWARD:
        case MSG_MOVE_HEARTBEAT:
        case CMSG_STANDSTATECHANGE:
        case CMSG_QUERY_TIME:
        case CMSG_CREATURE_QUERY:
        case CMSG_GAMEOBJECT_QUERY:
        case MSG_MOVE_JUMP:
        case MSG_MOVE_FALL_LAND:
            return;

        default:
        {
            const char* oc = LookupOpcodeName(packet.GetOpcode());
            // ChatHandler ch(m_master);
            // ch.SendSysMessage(oc);

            std::ostringstream out;
            out << "masterin: " << oc;
            sLog.outError(out.str().c_str());
        }
        */
    }
}
void PlayerbotMgr::HandleMasterOutgoingPacket(const WorldPacket& packet)
{
	/**
    switch (packet.GetOpcode())
    {
        // maybe our bots should only start looting after the master loots?
        //case SMSG_LOOT_RELEASE_RESPONSE: {} 
        case SMSG_NAME_QUERY_RESPONSE:
        case SMSG_MONSTER_MOVE:
        case SMSG_COMPRESSED_UPDATE_OBJECT:
        case SMSG_DESTROY_OBJECT:
        case SMSG_UPDATE_OBJECT:
        case SMSG_STANDSTATE_UPDATE:
        case MSG_MOVE_HEARTBEAT:
        case SMSG_QUERY_TIME_RESPONSE:
        case SMSG_AURA_UPDATE_ALL:
        case SMSG_CREATURE_QUERY_RESPONSE:
        case SMSG_GAMEOBJECT_QUERY_RESPONSE:
            return;
        default:
        {
            const char* oc = LookupOpcodeName(packet.GetOpcode());

            std::ostringstream out;
            out << "masterout: " << oc;
            sLog.outError(out.str().c_str());
        }
    }
	 */
}

void PlayerbotMgr::LogoutAllBots()
{
    while (true)
    {
        PlayerBotMap::const_iterator itr = GetPlayerBotsBegin();
        if (itr == GetPlayerBotsEnd()) break;
        Player* bot= itr->second;
        LogoutPlayerBot(bot->GetGUID());
    }
}

// Playerbot mod: logs out a Playerbot.
void PlayerbotMgr::LogoutPlayerBot(uint64 guid)
{
    Player* bot= GetPlayerBot(guid);
    if (bot)
    {
        WorldSession * botWorldSessionPtr = bot->GetSession();
        m_playerBots.erase(guid);    // deletes bot player ptr inside this WorldSession PlayerBotMap
        botWorldSessionPtr->LogoutPlayer(true); // this will delete the bot Player object and PlayerbotAI object
        delete botWorldSessionPtr;  // finally delete the bot's WorldSession
    }
}

// Playerbot mod: Gets a player bot Player object for this WorldSession master
Player* PlayerbotMgr::GetPlayerBot(uint64 playerGuid) const
{
    PlayerBotMap::const_iterator it = m_playerBots.find(playerGuid);
    return (it == m_playerBots.end()) ? 0 : it->second;
}

void PlayerbotMgr::OnBotLogin(Player * const bot)
{
    // give the bot some AI, object is owned by the player class
    PlayerbotAI* ai = new PlayerbotAI(this, bot);
    bot->SetPlayerbotAI(ai);

    // tell the world session that they now manage this new bot
    m_playerBots[bot->GetGUID()] = bot;

    // sometimes master can lose leadership, pass leadership to master check
    const uint64 masterGuid = m_master->GetGUID();
    if (m_master->GetGroup() && 
        ! m_master->GetGroup()->IsLeader(masterGuid))
        m_master->GetGroup()->ChangeLeader(masterGuid);
}

bool processBotCommand(WorldSession* session, string cmdStr, uint64 guid)
{
    if (guid == 0 || (guid == session->GetPlayer()->GetGUID()))
        return false;

    PlayerbotMgr* mgr = session->GetPlayer()->GetPlayerbotMgr();

    if (cmdStr == "add" || cmdStr == "login")
    {
        if (mgr->GetPlayerBot(guid)) 
            return false;
        
        mgr->AddPlayerBot(guid, session);
    }
    else if (cmdStr == "remove" || cmdStr == "logout")
    {
        if (! mgr->GetPlayerBot(guid))
            return false;
        
        mgr->LogoutPlayerBot(guid);
    }

    return true;
}

bool ChatHandler::HandlePlayerbotCommand(const char* args)
{
	if(sConfig.GetBoolDefault("PlayerbotAI.DisableBots", false))
	{
		PSendSysMessage("|cffff0000Playerbot system is currently disabled!");
        SetSentErrorMessage(true);
        return false;
	}

    if (! m_session)
    {
        PSendSysMessage("You may only add bots from an active session");
        SetSentErrorMessage(true);
        return false;
    }

    if (!*args)
    {
        PSendSysMessage("usage: add PLAYERNAME  or  remove PLAYERNAME");
        SetSentErrorMessage(true);
        return false;
    }

    char *cmd = strtok ((char*)args, " ");
    char *charname = strtok (NULL, " ");
    if (!cmd || !charname)
    {
        PSendSysMessage("usage: add PLAYERNAME  or  remove PLAYERNAME");
        SetSentErrorMessage(true);
        return false;
    }

    std::string cmdStr = cmd;
    std::string charnameStr = charname;

    Player* player = m_session->GetPlayer();

    // create the playerbot manager if it doesn't already exist
    PlayerbotMgr* mgr = player->GetPlayerbotMgr();
    if (!mgr)
    {
        mgr = new PlayerbotMgr(player);
        player->SetPlayerbotMgr(mgr);
    }

    if (charnameStr == "*")
    {
        Group* group = player->GetGroup();
        if (!group)
        {
            PSendSysMessage("you must be in group");
            SetSentErrorMessage(true);
            return false;
        }

        bool res = true;
        Group::MemberSlotList slots = group->GetMemberSlots();
        for (Group::member_citerator i = slots.begin(); i != slots.end(); i++) 
        {
            uint64 member = i->guid;
            if (member != player->GetGUID() && !processBotCommand(m_session, cmdStr, member))
            {
                PSendSysMessage("Error processing bot command");
                SetSentErrorMessage(true);
                res = false;
            }
        }
        return res;
    }
    else if (charnameStr.find(',') != string::npos)
    {
        int lastPos = 0;
        int pos = charnameStr.find(',');
        bool res = true;
        while (pos != string::npos)
        {
            string s = charnameStr.substr(lastPos, pos - lastPos);
            bool res = processBotCommand(m_session, cmdStr, sObjectMgr.GetPlayerGUIDByName(s.c_str()));
            if (!res)
            {
                PSendSysMessage("Error processing bot command");
                SetSentErrorMessage(true);
            }
            lastPos = pos + 1;
            pos = charnameStr.find(',', lastPos);
        }
        return res;
    }
    else
    {
        bool res = processBotCommand(m_session, cmdStr, sObjectMgr.GetPlayerGUIDByName(charnameStr.c_str()));
        if (!res)
        {
            PSendSysMessage("Error processing bot command");
            SetSentErrorMessage(true);
        }
        return res;
    }
}


void Creature::LoadBotMenu(Player *pPlayer)
{
    if (pPlayer->GetPlayerbotAI()) return;
    uint64 guid = pPlayer->GetGUID();
    uint32 accountId = sObjectMgr.GetPlayerAccountIdByGUID(guid);
    QueryResult *result = CharacterDatabase.PQuery("SELECT guid, name FROM characters WHERE account='%d'",accountId);
    do
    {
        Field *fields = result->Fetch();
        uint64 guidlo = fields[0].GetUInt64();
        std::string name = fields[1].GetString();
        std::string word = "";

        if( (guid == 0) || (guid == guidlo) )
        {
            //not found or himself
        }
        else
        {
			if(sConfig.GetBoolDefault("PlayerbotAI.DisableBots", false)) return;
            // create the manager if it doesn't already exist
            if (! pPlayer->GetPlayerbotMgr())
                pPlayer->SetPlayerbotMgr(new PlayerbotMgr(pPlayer));
            if(pPlayer->GetPlayerbotMgr()->GetPlayerBot(guidlo) == NULL) // add (if not already in game)
            {
                word += "Recruit ";
                word += name;
                word += " as a Bot.";
                pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem((uint8)9, word, guidlo, guidlo, word, false);
            }
            else if(pPlayer->GetPlayerbotMgr()->GetPlayerBot(guidlo) != NULL) // remove (if in game)
            {
                word += "Dismiss ";
                word += name;
                word += " from duty.";
                pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem((uint8)0, word, guidlo, guidlo, word, false);
            }
        }
    }
    while (result->NextRow());
    delete result;
}

bool Creature::isBotGiver()
{
    std::string scriptname = GetScriptName();
    if( scriptname == "bot_giver" )
        return true;
    return false;
}
