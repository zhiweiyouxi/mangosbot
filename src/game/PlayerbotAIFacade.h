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
    class PlayerbotAIFacade
    {
    public:
        PlayerbotAIFacade(PlayerbotAI* const ai) { this->ai = ai; }

    public:
        virtual float GetDistanceToEnemy();
        virtual void MoveToMaster() { ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetMaster(), 0, 0); }
        virtual void MoveToTarget() { ai->GetPlayerBot()->GetMotionMaster()->MoveFollow(ai->GetCurrentTarget(), 0, 0); }
        virtual void CastSpell(const char* spell) { ai->CastSpell(ai->getSpellId(spell)); }
        virtual BOOL canCastSpell( const char* spell );
    protected:
        PlayerbotAI *ai;
    };
}