#include "PlayerbotClassAI.h"
#include "Common.h"
#include "AiFactory.h"

using namespace std;
using namespace ai;

PlayerbotClassAI::PlayerbotClassAI(Player* bot, AiManagerRegistry* aiRegistry)
{
	this->bot = bot;
	this->aiRegistry = aiRegistry;

	combatEngine = AiFactory::createCombatEngine(bot, aiRegistry);
	nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry);

	currentEngine = nonCombatEngine;
}

PlayerbotClassAI::~PlayerbotClassAI() 
{
	currentEngine = NULL;

    if (combatEngine) 
	{
        delete combatEngine;
        combatEngine = NULL;
    }
    if (nonCombatEngine) 
	{
        delete nonCombatEngine;
        nonCombatEngine = NULL;
    }
}

void PlayerbotClassAI::DoNextAction() 
{
	Unit* target = aiRegistry->GetTargetManager()->GetCurrentTarget();
	if (target && target->isAlive() && target->IsHostileTo(bot))
	{
		currentEngine = combatEngine;
	}
	else 
    {
        bot->SetSelection(0);
        if (!bot->isInCombat() && currentEngine != nonCombatEngine)
	    {
		    aiRegistry->GetSpellManager()->InterruptSpell();
		    currentEngine = nonCombatEngine;
	    }
    }

	currentEngine->DoNextAction(NULL);
}

void PlayerbotClassAI::ChangeStrategy( const char* name, Engine* e ) 
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
    case '?':
        aiRegistry->GetSocialManager()->TellMaster(e->ListStrategies().c_str());
        break;
    }
}

void PlayerbotClassAI::DoSpecificAction(const char* name) 
{ 
	if (!currentEngine) 
		return;
	
	if (!currentEngine->ExecuteAction(name))
	{
		aiRegistry->GetSocialManager()->TellMaster("Action failed: ");
		aiRegistry->GetSocialManager()->TellMaster(name);
	}
}