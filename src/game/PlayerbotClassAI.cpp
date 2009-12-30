#include "PlayerbotClassAI.h"
#include "Common.h"

PlayerbotClassAI::PlayerbotClassAI(Player* const master, Player* const bot, PlayerbotAI* const ai): m_master(master), m_bot(bot), m_ai(ai) 
{
    engine = NULL; // must be created in subclasses
}

PlayerbotClassAI::~PlayerbotClassAI() 
{
    if (engine) delete engine;
}

bool PlayerbotClassAI::DoFirstCombatManeuver(Unit *) 
{
    // return false, if done with opening moves/spells
    return false;
}
void PlayerbotClassAI::DoNextCombatManeuver(Unit *) {}

void PlayerbotClassAI::DoNonCombatActions(){}

void PlayerbotClassAI::BuffPlayer(Player* target) {}

void PlayerbotClassAI::ChangeStrategy( const char* name )
{
    if (!engine)
        return;
    
    switch (name[0])
    {
    case '+':
        engine->addStrategy(name+1);
        break;
    case '-':
        engine->removeStrategy(name+1);
        break;
    default:
        engine->clearStrategies();
        engine->addStrategy(name);
        break;
    }
    
}
