#pragma once

using namespace std;

namespace ai 
{
    class AiManagerRegistry;
    class AiManagerBase;

	class AiSocialManager : public AiManagerBase
	{
	public:
		AiSocialManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual void Emote(uint32 emote);
		virtual void TellMaster(const char* text);
		virtual void LeaveGroup();
		virtual void AcceptInvitation();
	
	public:
		virtual void HandleCommand(const string& text, Player& fromPlayer);
		virtual void HandleBotOutgoingPacket(const WorldPacket& packet);
	};

};