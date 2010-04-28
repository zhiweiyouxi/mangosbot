#include "pchdef.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "TankPaladinStrategy.h"
#include "PaladinActions.h"

using namespace ai;

NextAction** TankPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void TankPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new JudgementOfLightTrigger(ai), 
        NextAction::array(0, new NextAction("judgement of light", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        new RighteousFuryTrigger(ai), 
        NextAction::array(0, new NextAction("righteous fury", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack bigger threat", 9.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 2), 
        NextAction::array(0, new NextAction("holy wrath", 50.0f), new NextAction("avenger's shield", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LoseAggroTrigger(ai), 
        NextAction::array(0, new NextAction("hand of reckoning", 60.0f), new NextAction("exorcism", 60.0f), NULL)));

}

void TankPaladinStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("judgement of light", name)) 
    {
        return new ActionNode (new CastJudgementOfLightAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("holy wrath", name)) 
    {
        return new ActionNode (new CastHolyWrathAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("consecration"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("consecration", name)) 
    {
        return new ActionNode (new CastConsecrationAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("righteous fury", name)) 
    {
        return new ActionNode (new CastRighteousFuryAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("hand of reckoning", name)) 
    {
        return new ActionNode (new CastHandOfReckoningAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of justice"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("avenger's shield", name)) 
    {
        return new ActionNode (new CastAvengersShieldAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("exorcism", name)) 
	{
		return new ActionNode (new CastExorcismAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return GenericPaladinStrategy::createAction(name);
}