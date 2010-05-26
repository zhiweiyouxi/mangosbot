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
#include "AiManagerRegistry.h"

class Player;
class PlayerbotAI;

#include "Engine.h"

using namespace ai;
using namespace std;


class MANGOS_DLL_SPEC PlayerbotClassAI
{
public:
    PlayerbotClassAI(Player* bot, AiManagerRegistry* aiRegistry);
    virtual ~PlayerbotClassAI();

    virtual void DoNextAction();

    void DoSpecificAction(const char* name);
    void ChangeStrategy( const char* name, Engine* e );
    void ChangeCombatStrategy(const char* name) { ChangeStrategy(name, combatEngine); }
    void ChangeNonCombatStrategy(const char* name) { ChangeStrategy(name, nonCombatEngine); }

protected:
    AiManagerRegistry *aiRegistry;
	Player* bot;

protected:
	Engine* currentEngine;
    Engine* combatEngine;
    Engine* nonCombatEngine;
};

#endif
