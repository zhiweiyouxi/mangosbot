#include "pchdef.h"
#include "WarriorTriggers.h"
#include "GenericWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

void GenericWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new AndTrigger(ai, new RageAvailable(ai, 40), new AttackerCountTrigger(ai, 2)),
        NextAction::array(0, new NextAction("cleave", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new BattleShoutTrigger(ai), 
        NextAction::array(0, new NextAction("battle shout", 80.0f), NULL)));

    /*triggers.push_back(new TriggerNode(
        new RevengeAvailableTrigger(ai), 
        NextAction::array(0, new NextAction("revenge", 50.0f), NULL)));*/
    
    triggers.push_back(new TriggerNode(
        new RendDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("rend", 1.3f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 2), 
        NextAction::array(0, new NextAction("demoralizing shout", 23.0f), new NextAction("thunder clap", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 3), 
        NextAction::array(0, new NextAction("challenging shout", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("lifeblood", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new BloodrageDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("bloodrage", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new InterruptSpellTrigger(ai, "shield bash"), 
        NextAction::array(0, new NextAction("shield bash", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai, 5), 
		NextAction::array(0, new NextAction("intimidating shout", 90.0f), NULL)));
}


ActionNode* GenericWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("hamstring", name)) 
    {
        return new ActionNode (new CastHamstringAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield bash", name)) 
    {
        return new ActionNode (new CastShieldBashAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield block", name)) 
    {
        return new ActionNode (new CastShieldBlockAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("bloodrage", name)) 
    {
        return new ActionNode (new CastBloodrageAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("defensive stance", name)) 
    {
        return new ActionNode (new CastDefensiveStanceAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("gift of the naaru", name)) 
    {
        return new ActionNode (new CastGiftOfTheNaaruAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("battle stance", name)) 
    {
        return new ActionNode (new CastBattleStanceAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("heroic strike", name)) 
    {
        return new ActionNode (new CastHeroicStrikeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cleave", name)) 
    {
        return new ActionNode (new CastCleaveAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("intimidating shout", name)) 
	{
		return new ActionNode (new CastIntimidatingShoutAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("demoralizing shout", name)) 
    {
        return new ActionNode (new CastDemoralizingShoutAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("challenging shout", name)) 
    {
        return new ActionNode (new CastChallengingShoutAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield wall", name)) 
    {
        return new ActionNode (new CastShieldWallAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("battle shout", name)) 
    {
        return new ActionNode (new CastBattleShoutAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("thunder clap", name)) 
    {
        return new ActionNode (new CastThunderClapAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}
