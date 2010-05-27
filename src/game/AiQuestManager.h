#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "Item.h"

using namespace std;

namespace ai 
{
	class AiQuestManager;

	class AiQuestManager : public AiManagerBase
	{
	public:
		AiQuestManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		void UpdateQuestNeedItems();
		void ListQuests();
		void DropQuest(const char* link);
		void QuestLocalization(std::string& questTitle, const uint32 questID);
		map<uint32, uint32> GetQuestItems() { return questNeedItems; }

	private:
		map<uint32, uint32> questNeedItems;
	};

};