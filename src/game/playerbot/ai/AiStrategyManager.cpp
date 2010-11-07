#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiStrategyManager.h"
#include "../strategy/Engine.h"
#include "AiFactory.h"

using namespace std;
using namespace ai;

AiStrategyManager::AiStrategyManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : 
	AiManagerBase(ai, aiRegistry)
{
    if (!aiRegistry)
        return;

	combatEngine = AiFactory::createCombatEngine(bot, aiRegistry);
	nonCombatEngine = AiFactory::createNonCombatEngine(bot, aiRegistry);

	currentEngine = nonCombatEngine;
}

AiStrategyManager::~AiStrategyManager() 
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

void AiStrategyManager::DoNextAction() 
{
	WorldPacket data;
	bot->BuildHeartBeatMsg( &data );
	bot->SendMessageToSet( &data, false );
	bot->SetPosition( bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetOrientation(), false );

	Unit* target = aiRegistry->GetTargetManager()->GetCurrentTarget();
	if (target && target->isAlive() && target->IsHostileTo(bot))
	{
        if (currentEngine != combatEngine)
        {
            currentEngine = combatEngine;
            ReInitCurrentEngine();
        }
	}
	else 
    {
        aiRegistry->GetTargetManager()->SetCurrentTarget(NULL);
        bot->SetSelection(0);
        if (currentEngine != nonCombatEngine)
	    {
		    currentEngine = nonCombatEngine;
            ReInitCurrentEngine();
	    }
    }

    AiManagerBase** managers = aiRegistry->GetManagers();
    for (int i=0; i<aiRegistry->GetManagerCount(); i++)
        managers[i]->Update();

	currentEngine->DoNextAction(NULL);
}

void AiStrategyManager::ReInitCurrentEngine()
{
    aiRegistry->GetSpellManager()->InterruptSpell();
    currentEngine->Init();
    ai->SetNextCheckDelay(0);
}

void AiStrategyManager::ChangeStrategy( const char* names, Engine* e ) 
{
    if (!e)
        return;
    
    vector<string> splitted = split(names, ',');
    for (vector<string>::iterator i = splitted.begin(); i != splitted.end(); i++)
    {
        const char* name = i->c_str();
        switch (name[0]) 
	    {
        case '+':
            e->addStrategy(name+1);
            break;
        case '-':
            e->removeStrategy(name+1);
            break;
        case '~':
            e->toggleStrategy(name+1);
            break;
        case '?':
            aiRegistry->GetSocialManager()->TellMaster(e->ListStrategies().c_str());
            break;
        }
    }
}

void AiStrategyManager::DoSpecificAction(const char* name) 
{ 
	if (!combatEngine->ExecuteAction(name) && !nonCombatEngine->ExecuteAction(name))
	{
		aiRegistry->GetSocialManager()->TellMaster("Action failed: ");
		aiRegistry->GetSocialManager()->TellMaster(name);
        return;
	}
}

void AiStrategyManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text.size() > 2 && text.substr(0, 2) == "d " || text.size() > 3 && text.substr(0, 3) == "do ")
	{
		std::string action = text.substr(text.find(" ") + 1);
		DoSpecificAction(action.c_str());
	}

	else if (text.size() > 3 && text.substr(0, 3) == "co ")
	{
		std::string strategy = text.substr(text.find(" ") + 1);
		ChangeCombatStrategy(strategy.c_str());
	}

	else if (text.size() > 3 && text.substr(0, 3) == "nc ")
	{
		std::string strategy = text.substr(text.find(" ") + 1);
		ChangeNonCombatStrategy(strategy.c_str());
	}
    else if (text == "reset")
    {
        combatEngine->Init();
        nonCombatEngine->Init();
        currentEngine = nonCombatEngine;
    }
}

void AiStrategyManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
}

bool AiStrategyManager::ContainsStrategy(StrategyType type)
{
	return combatEngine->ContainsStrategy(type) || nonCombatEngine->ContainsStrategy(type);

    void AfterEngineChanged();
}

