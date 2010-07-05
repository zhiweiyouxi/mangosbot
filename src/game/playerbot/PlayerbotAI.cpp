#include "../pchdef.h"
#include "playerbot.h"



using namespace ai;
using namespace std;

vector<string>& split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    return split(s, delim, elems);
}

PlayerbotAI::PlayerbotAI() : PlayerbotAIBase()
{
	aiRegistry = NULL;
}

PlayerbotAI::PlayerbotAI(PlayerbotMgr* mgr, Player* bot) : PlayerbotAIBase()
{
	this->mgr = mgr;
	this->bot = bot;
	aiRegistry = new AiManagerRegistry(this);
}

PlayerbotAI::~PlayerbotAI()
{
	if (aiRegistry)
		delete aiRegistry;
}

void PlayerbotAI::UpdateAI(uint32 elapsed)
{
	if (!CanUpdateAI())
		return;

    if (bot->IsBeingTeleported() || bot->GetTrader())
        return;

    UpdateNextCheckDelay();

	if (bot->isAlive())
		aiRegistry->GetStrategyManager()->DoNextAction();
	else
		aiRegistry->GetMoveManager()->Resurrect();

	YieldThread();
}

void PlayerbotAI::HandleTeleportAck()
{
	bot->GetMotionMaster()->Clear(true);
	if (bot->IsBeingTeleportedNear())
	{
		WorldPacket p = WorldPacket(MSG_MOVE_TELEPORT_ACK, 8 + 4 + 4);
		p.appendPackGUID(bot->GetGUID());
		p << (uint32) 0; // supposed to be flags? not used currently
		p << (uint32) time(0); // time - not currently used
		bot->GetSession()->HandleMoveTeleportAck(p);
	}
	else if (bot->IsBeingTeleportedFar())
		bot->GetSession()->HandleMoveWorldportAckOpcode();
}

void PlayerbotAI::HandleCommand(const string& text, Player& fromPlayer)
{
	// ignore any messages from Addons
	if (text.empty() ||
		text.find("X-Perl") != wstring::npos ||
		text.find("HealBot") != wstring::npos ||
		text.find("LOOT_OPENED") != wstring::npos ||
		text.find("CTRA") != wstring::npos)
		return;

	if (fromPlayer.GetGuildId() != bot->GetGuildId())
	    return;

	AiManagerBase** managers = aiRegistry->GetManagers();

    if (text.size() > 2 && text.substr(0, 2) == "q ")
    {
        string query = text.substr(text.find(" ") + 1);
        for (int i=0; i<aiRegistry->GetManagerCount(); i++)
            managers[i]->Query(query);
        return;
    }
    else if (text == "reset") 
    {
        nextAICheckTime = 0;
    }

	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleCommand(text, fromPlayer);
}

void PlayerbotAI::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	AiManagerBase** managers = aiRegistry->GetManagers();
	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleBotOutgoingPacket(packet);
}

void PlayerbotAI::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    AiManagerBase** managers = aiRegistry->GetManagers();
    for (int i=0; i<aiRegistry->GetManagerCount(); i++)
        managers[i]->HandleMasterIncomingPacket(packet);
}

void PlayerbotAI::UpdateNextCheckDelay()
{
    int delay = 1;
    
    Group* group = bot->GetGroup();
    if (group) 
        delay += group->GetMembersCount() / 10;
    
    SetNextCheckDelay(delay);
}