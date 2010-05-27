#pragma once

#include "Player.h"
#include "PlayerbotAIBase.h"
#include "AiManagerBase.h"
#include "Item.h"

using namespace std;

namespace ai 
{
	class AiManagerRegistry;

	class AiSocialManager : public AiManagerBase
	{
	public:
		AiSocialManager(PlayerbotAIBase* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
		{
		}

	public:
		virtual void Emote(uint32 emote);
		virtual void TellMaster(const char* text);
		virtual void Trade(const char* text);
		virtual void LeaveGroup();
		virtual void AcceptInvitation();
		virtual void AcceptTrade();
		virtual void BeginTrade();

	private:
		bool TradeItem(const Item& item, int8 slot = -1);
		uint32 extractMoney(const std::string& text);
	};

};