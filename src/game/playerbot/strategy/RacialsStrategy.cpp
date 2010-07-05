#include "../../pchdef.h"
#include "../playerbot.h"
#include "RacialsStrategy.h"
#include "HealthTriggers.h"
#include "GenericSpellActions.h"
#include "GenericTriggers.h"

using namespace ai;

void RacialsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai), 
		NextAction::array(0, new NextAction("lifeblood", 71.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowManaTrigger(ai), 
        NextAction::array(0, new NextAction("arcane torrent", 55.0f), NULL)));
}


ActionNode* RacialsStrategy::createAction(const char* name)
{
	if (!strcmp("lifeblood", name)) 
	{
		return new ActionNode (new CastLifeBloodAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("gift of the naaru"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("gift of the naaru", name)) 
	{
		return new ActionNode (new CastGiftOfTheNaaruAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("arcane torrent", name)) 
    {
        return new ActionNode (new CastArcaneTorrentAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else return NULL;
}

