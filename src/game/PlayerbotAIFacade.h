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

class PlayerbotAIFacade
{
public:
    PlayerbotAIFacade(PlayerbotAI* const ai) { this->ai = ai; }

public:
    virtual float GetDistanceToEnemy();
    virtual void MoveToMaster() { ai->GetPlayerBot()->GetMotionMaster()->MoveChase(ai->GetMaster()); }
    virtual void CastSpell(const char* spell) { ai->CastSpell(ai->getSpellId(spell)); }
    virtual BOOL canCastSpell( const char* spell );
protected:
    PlayerbotAI *ai;
};