#include "PlayerbotClassAI.h"
#include "Common.h"
#include "AiFactory.h"

using namespace std;
using namespace ai;

PlayerbotClassAI::PlayerbotClassAI(Player* const bot, AiManagerRegistry* aiRegistry)
{
	this->aiRegistry = aiRegistry;
	engine = AiFactory::createCombatEngine(bot, aiRegistry);
	nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry);
}

PlayerbotClassAI::~PlayerbotClassAI() {
    if (engine) {
        delete engine;
        engine = NULL;
    }
    if (nonCombatEngine) {
        delete nonCombatEngine;
        nonCombatEngine = NULL;
    }
}

void PlayerbotClassAI::DoCombatAction(Unit *target) {
	engine->DoNextAction(target);
}

void PlayerbotClassAI::DoNonCombatAction() {
	nonCombatEngine->DoNextAction(NULL);
}

void PlayerbotClassAI::ChangeStrategy( const char* name, Engine* e ) {
    if (!e)
        return;
    
    switch (name[0]) {
    case '+':
        e->addStrategy(name+1);
        break;
    case '-':
        e->removeStrategy(name+1);
        break;
    case '?':
        aiRegistry->GetSocialManager()->TellMaster(e->ListStrategies().c_str());
        break;
    }
}

void PlayerbotClassAI::DoSpecificAction(const char* name) 
{ 
	if (!engine) 
		return;
	
	if (!engine->ExecuteAction(name))
	{
		aiRegistry->GetSocialManager()->TellMaster("Action failed: ");
		aiRegistry->GetSocialManager()->TellMaster(name);
	}
}