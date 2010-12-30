#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "HunterBuffStrategies.h"
#include "HunterActions.h"

using namespace ai;

void HunterBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new HunterAspectOfTheHawkTrigger(ai), 
		NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));
}

void HunterNatureResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new HunterAspectOfTheWildTrigger(ai), 
		NextAction::array(0, new NextAction("aspect of the wild", 90.0f), NULL)));
}
