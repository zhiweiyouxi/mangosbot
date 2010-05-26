#pragma once

#include "PlayerbotAI.h"
#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"

namespace ai
{
    struct FindPlayerParam
    {
        PlayerbotAI *ai;
        void* param;
    };


    class PlayerbotAIFacade
    {
    public:
        PlayerbotAIFacade(PlayerbotAI* const ai) { this->ai = ai; }

	public:
		virtual AiSpellManager* GetSpellManager() { return ai->GetSpellManager(); }
		virtual AiTargetManager* GetTargetManager() { return ai->GetTargetManager(); }
		virtual AiStatsManager* GetStatsManager() { return ai->GetStatsManager(); }
		virtual AiMoveManager* GetMoveManager() { return ai->GetMoveManager(); }
		virtual AiInventoryManager* GetInventoryManager() { return ai->GetInventoryManager(); }

    public:
        virtual void Attack(Unit* target);
        virtual void TellMaster(const char* text) { ai->TellMaster(text); }        
        virtual void Emote(uint32 emote);

    protected:
        PlayerbotAI *ai;
    };

}