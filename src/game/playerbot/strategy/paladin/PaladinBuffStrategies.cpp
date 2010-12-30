#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "PaladinBuffStrategies.h"
#include "PaladinActions.h"

using namespace ai;

void PaladinBuffManaStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of wisdom", 24.0f), NULL)));
}

void PaladinBuffHealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of light", 24.0f), NULL)));
}

void PaladinBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new SealTrigger(ai), 
        NextAction::array(0, new NextAction("seal of command", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "retribution aura"), 
		NextAction::array(0, new NextAction("retribution aura", 25.0f), NULL)));
}

void PaladinShadowResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "shadow resistance aura"), 
		NextAction::array(0, new NextAction("shadow resistance aura", 24.0f), NULL)));
}

void PaladinFrostResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "frost resistance aura"), 
		NextAction::array(0, new NextAction("frost resistance aura", 24.0f), NULL)));
}

void PaladinFireResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "fire resistance aura"), 
		NextAction::array(0, new NextAction("fire resistance aura", 24.0f), NULL)));
}


void PaladinBuffArmorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		new BuffTrigger(ai, "devotion aura"), 
		NextAction::array(0, new NextAction("devotion aura", 25.0f), NULL)));
}

