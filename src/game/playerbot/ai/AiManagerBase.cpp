#include "../../pchdef.h"
#include "../playerbot.h"


using namespace ai;
using namespace std;

uint32 PlayerbotChatHandler::extractQuestId(const char *str)
{
    char* cId = extractKeyFromLink((char*)str,"Hquest");
    return cId ? atol(cId) : 0;
}

AiManagerBase::AiManagerBase(PlayerbotAI* ai, AiManagerRegistry* aiRegistry)
{
	this->ai = ai;
	this->bot = ai->GetBot();
	this->aiRegistry = aiRegistry;
}

uint64 AiManagerBase::extractGuid(WorldPacket& packet)
{
	uint8 mask;
	packet >> mask;
	uint64 guid = 0;
	uint8 bit = 0;
	uint8 testMask = 1;
	while (true)
	{
		if (mask & testMask)
		{
			uint8 word;
			packet >> word;
			guid += (word << bit);
		}
		if (bit == 7)
			break;
		++bit;
		testMask <<= 1;
	}
	return guid;
}