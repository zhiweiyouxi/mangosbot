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
