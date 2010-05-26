#ifndef _PLAYERBOTCLASSAI_H
#define _PLAYERBOTCLASSAI_H

#include "Common.h"
#include "World.h"
#include "SpellMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "WorldPacket.h"
#include "Unit.h"
#include "SharedDefines.h"
#include "PlayerbotAI.h"

#include "Engine.h"
#include "PlayerbotAIFacade.h"

class Player;
class PlayerbotAI;

#include "Engine.h"

class MANGOS_DLL_SPEC PlayerbotClassAI
{
public:
    PlayerbotClassAI(Player* const master, Player* const bot, PlayerbotAI* const ai);
    virtual ~PlayerbotClassAI();

    virtual void DoCombatAction(Unit*);
    virtual void DoNonCombatAction();

    void DoSpecificAction(const char* name);
    void ChangeStrategy( const char* name, ai::Engine* e );
    void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, engine); }
    void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }

private:
    Player* m_master;
    Player* m_bot;
    PlayerbotAI* m_ai;

protected:
    ai::PlayerbotAIFacade *facade;

protected:
    ai::Engine* engine;
    ai::Engine* nonCombatEngine;
};

#endif
