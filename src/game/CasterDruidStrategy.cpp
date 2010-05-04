#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "DruidActions.h"
#include "CasterDruidStrategy.h"

using namespace ai;


NextAction** CasterDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("starfire", 11.0f), new NextAction("wrath", 10.0f), NULL);
}

void CasterDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		new InsectSwarmTrigger(ai),
		NextAction::array(0, new NextAction("insect swarm", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new MoonfireTrigger(ai),
		NextAction::array(0, new NextAction("moonfire", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new FaerieFireTrigger(ai),
		NextAction::array(0, new NextAction("faerie fire", 16.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new EnemyTooCloseTrigger(ai),
		NextAction::array(0, new NextAction("entangling roots", 50.0f), NULL)));

}

void CasterDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* CasterDruidStrategy::createAction(const char* name)
{
    if (!strcmp("faerie fire", name)) 
    {
        return new ActionNode (new CastFaerieFireAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("moonkin form", name)) 
    {
        return new ActionNode (new CastMoonkinFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("entangling roots", name)) 
	{
		return new ActionNode (new CastEntanglingRootsAction(ai),  
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL, 
			/*C*/ NextAction::array(0, new NextAction("flee", 50.0f), NULL));
	}
	else if (!strcmp("wrath", name)) 
	{
		return new ActionNode (new CastWrathAction(ai),  
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("insect swarm", name)) 
	{
		return new ActionNode (new CastInsectSwarmAction(ai),  
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("moonfire", name)) 
	{
		return new ActionNode (new CastMoonfireAction(ai),  
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("starfire", name)) 
	{
		return new ActionNode (new CastStarfireAction(ai),  
			/*P*/ NextAction::array(0, new NextAction("moonkin form"), NULL),
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return GenericDruidStrategy::createAction(name);
}