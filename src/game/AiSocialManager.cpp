#include "pchdef.h"
#include "AiSocialManager.h"
#include "AiManagerRegistry.h"
#include "Spell.h"
#include "WorldPacket.h"
#include "LootMgr.h"

using namespace ai;
using namespace std;

void AiSocialManager::Emote(uint32 emote)
{
	bot->HandleEmoteCommand(emote);
}

void AiSocialManager::TellMaster(const char* text)
{
	WorldPacket data(SMSG_MESSAGECHAT, 200);
	bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
	ai->GetMaster()->GetSession()->SendPacket(&data);
}
