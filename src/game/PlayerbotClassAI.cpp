#include "PlayerbotClassAI.h"
#include "Common.h"
#include "AiFactory.h"

PlayerbotClassAI::PlayerbotClassAI(Player* const master, Player* const bot, PlayerbotAI* const ai) : 
		m_master(master), m_bot(bot), m_ai(ai)  {
    facade = new ai::PlayerbotAIFacade(ai);
	engine = AiFactory::createCombatEngine(bot, facade);
	nonCombatEngine = AiFactory::createNonCombatEngine(bot, facade);
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
    if (facade) {
        delete facade;
        facade = NULL;
    }
}

void PlayerbotClassAI::DoCombatAction(Unit *target) {
	engine->DoNextAction(target);
}

void PlayerbotClassAI::DoNonCombatAction() {
	nonCombatEngine->DoNextAction(NULL);
}

void PlayerbotClassAI::ChangeStrategy( const char* name, ai::Engine* e ) {
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
        m_ai->TellMaster(e->ListStrategies());
        break;
    }
}
