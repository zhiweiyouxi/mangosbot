#include "PlayerbotClassAI.h"
#include "Common.h"

PlayerbotClassAI::PlayerbotClassAI(Player* const master, Player* const bot, PlayerbotAI* const ai): m_master(master), m_bot(bot), m_ai(ai) 
{
    engine = NULL; // must be created in subclasses
    nonCombatEngine = NULL;
    facade = new ai::PlayerbotAIFacade(ai);
}

PlayerbotClassAI::~PlayerbotClassAI() 
{
    if (engine) delete engine;
    if (nonCombatEngine) delete nonCombatEngine;
    if (facade) delete facade;
}

bool PlayerbotClassAI::DoFirstCombatManeuver(Unit *) 
{
    // return false, if done with opening moves/spells
    return false;
}
void PlayerbotClassAI::DoNextCombatManeuver(Unit *) {}

void PlayerbotClassAI::DoNonCombatActions(){}

void PlayerbotClassAI::BuffPlayer(Player* target) {}

void PlayerbotClassAI::ChangeStrategy( const char* name, ai::Engine* e )
{
    if (!e)
        return;
    
    switch (name[0])
    {
    case '+':
        e->addStrategy(name+1);
        break;
    case '-':
        e->removeStrategy(name+1);
        break;
    default:
        e->clearStrategies();
        e->addStrategy(name);
        break;
    }
    
}
