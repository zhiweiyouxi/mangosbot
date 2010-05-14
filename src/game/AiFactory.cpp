#include "pchdef.h"
#include "AiFactory.h"

#include "PriestActionFactory.h"
#include "MageActionFactory.h"
#include "WarlockActionFactory.h"
#include "WarriorActionFactory.h"
#include "ShamanActionFactory.h"
#include "PaladinActionFactory.h"
#include "DruidActionFactory.h"
#include "HunterActionFactory.h"
#include "RogueActionFactory.h"

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAIFacade* const facade) {
	Engine* engine = NULL;

	switch (player->getClass())
    {
        case CLASS_PRIEST:
			engine = new Engine(facade, new PriestActionFactory(facade));
			engine->addStrategies("heal", "dps assist", NULL);
            break;
        case CLASS_MAGE:
			engine = new Engine(facade, new MageActionFactory(facade));
			engine->addStrategies("frost", "dps assist", NULL);
            break;
        case CLASS_WARLOCK:
			engine = new Engine(facade, new WarlockActionFactory(facade));
			engine->addStrategies("dps", "dps assist", NULL);
            break;
        case CLASS_WARRIOR:
			engine = new Engine(facade, new WarriorActionFactory(facade));
			engine->addStrategies("tank", "tank assist", NULL);
            break;
        case CLASS_SHAMAN:
			engine = new Engine(facade, new ShamanActionFactory(facade));
			engine->addStrategies("heal", "dps assist", NULL);
            break;
        case CLASS_PALADIN:
			engine = new Engine(facade, new PaladinActionFactory(facade));
			engine->addStrategies("tank", "tank assist", NULL);
            break;
        case CLASS_DRUID:
			engine = new Engine(facade, new DruidActionFactory(facade));
			engine->addStrategies("caster", "dps assist", NULL);
            break;
        case CLASS_HUNTER:
			engine = new Engine(facade, new HunterActionFactory(facade));
			engine->addStrategies("dps", "dps assist", NULL);
            break;
		case CLASS_ROGUE:
			engine = new Engine(facade, new RogueActionFactory(facade));
			engine->addStrategies("dps", "dps assist", NULL);
			break;
    }
	return engine;
}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAIFacade* const facade) {
	Engine* nonCombatEngine = NULL;
	switch (player->getClass())
    {
        case CLASS_PRIEST:
			nonCombatEngine = new Engine(facade, new PriestActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_MAGE:
			nonCombatEngine = new Engine(facade, new MageActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_WARLOCK:
			nonCombatEngine = new Engine(facade, new WarlockActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_WARRIOR:
			nonCombatEngine = new Engine(facade, new WarriorActionFactory(facade));
			nonCombatEngine->addStrategy("tank assist");
            break;
        case CLASS_SHAMAN:
			nonCombatEngine = new Engine(facade, new ShamanActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_PALADIN:
			nonCombatEngine = new Engine(facade, new PaladinActionFactory(facade));
			nonCombatEngine->addStrategy("tank assist");
            break;
        case CLASS_DRUID:
			nonCombatEngine = new Engine(facade, new DruidActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
        case CLASS_HUNTER:
			nonCombatEngine = new Engine(facade, new HunterActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
            break;
		case CLASS_ROGUE:
			nonCombatEngine = new Engine(facade, new RogueActionFactory(facade));
			nonCombatEngine->addStrategy("dps assist");
			break;
    }
    nonCombatEngine->addStrategies("nc", "emote", "food", "stay", NULL);
	return nonCombatEngine;
}