#pragma once

#include "Player.h"
#include "PlayerbotAI.h"
#include "AiManagerBase.h"
#include "Item.h"

using namespace std;

namespace ai 
{
	class AiQuestManager;

	class AiQuestManager : public AiManagerBase
	{
	public:
		AiQuestManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		void UpdateQuestNeedItems();
		void ListQuests();
		void DropQuest(const char* link);
		void QuestLocalization(std::string& questTitle, const uint32 questID);
		map<uint32, uint32> GetQuestItems() { return questNeedItems; }
		void TurnInQuests( WorldObject *questgiver );
		void AcceptQuest( Quest const *qInfo, Player *pGiver );

	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);

	private:
		map<uint32, uint32> questNeedItems;
	};

};