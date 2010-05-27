#include "pchdef.h"
#include "AiQuestManager.h"
#include "AiManagerRegistry.h"
#include "AiInventoryManager.h"
#include "AiSocialManager.h"

using namespace ai;
using namespace std;

void AiQuestManager::UpdateQuestNeedItems()
{
	questNeedItems.clear();

	for( QuestStatusMap::iterator iter=bot->getQuestStatusMap().begin(); iter!=bot->getQuestStatusMap().end(); ++iter )
	{
		const Quest *qInfo = sObjectMgr.GetQuestTemplate( iter->first );
		if( !qInfo )
			continue;

		QuestStatusData *qData = &iter->second;
		if( qData->m_status != QUEST_STATUS_INCOMPLETE )
			continue;

		for( int i=0; i<QUEST_OBJECTIVES_COUNT; i++ )
		{
			if( !qInfo->ReqItemCount[i] || (qInfo->ReqItemCount[i]-qData->m_itemcount[i])<=0 )
				continue;
			questNeedItems[qInfo->ReqItemId[i]] = (qInfo->ReqItemCount[i]-qData->m_itemcount[i]);
		}
	}
}

void AiQuestManager::ListQuests()
{
	std::ostringstream res;

	bool hasIncompleteQuests = false;
	std::ostringstream incomout;
	incomout << "my incomplete quests are:";
	
	bool hasCompleteQuests = false;
	std::ostringstream comout;
	comout << "my complete quests are:";
	
	for (uint16 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
	{
		if(uint32 questId = bot->GetQuestSlotQuestId(slot))
		{
			Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);
			if (bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE) {
				hasCompleteQuests = true;
				comout << " |cFFFFFF00|Hquest:" << questId << ':' << pQuest->GetQuestLevel() << "|h[" << pQuest->GetTitle() << "]|h|r";
			}
			else {
				hasIncompleteQuests = true;
				incomout << " |cFFFFFF00|Hquest:" << questId << ':' << pQuest->GetQuestLevel() << "|h[" << pQuest->GetTitle() << "]|h|r";
			}
		}
	}

	res << comout.str();
	res << incomout.str();

	aiRegistry->GetSocialManager()->TellMaster(res.str().c_str());
}

void AiQuestManager::DropQuest(const char* link)
{
	PlayerbotChatHandler ch(ai->GetMaster());
	if (!ch.dropQuest(link))
	{
		aiRegistry->GetSocialManager()->TellMaster("Could not drop quest: ");
		aiRegistry->GetSocialManager()->TellMaster(link);
	}
}

void AiQuestManager::QuestLocalization(std::string& questTitle, const uint32 questID)
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbLocaleIndex();
	std::wstring wnamepart;

	QuestLocale const *pQuestInfo = sObjectMgr.GetQuestLocale(questID);
	if (pQuestInfo)
	{
		if (pQuestInfo->Title.size() > loc && !pQuestInfo->Title[loc].empty())
		{
			const std::string title = pQuestInfo->Title[loc];
			if (Utf8FitTo(title, wnamepart))
				questTitle = title.c_str();
		}
	}
}
