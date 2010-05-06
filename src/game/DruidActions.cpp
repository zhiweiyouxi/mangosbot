#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

bool CastRejuvenationAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("lifeblood");
}

bool CastRejuvenationAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

bool CastRegrowthAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

bool CastCasterFormAction::ExecuteResult()
{
    if (ai->HasAura("dire bear form")) 
        ai->RemoveAura("dire bear form");
    else if (ai->HasAura("bear form")) 
        ai->RemoveAura("bear form");
    else if (ai->HasAura("cat form")) 
        ai->RemoveAura("cat form");
	else if (ai->HasAura("moonkin form")) 
		ai->RemoveAura("moonkin form");
    else if (ai->HasAura("travel form")) 
        ai->RemoveAura("travel form");
	else if (ai->HasAura("aquatic form")) 
		ai->RemoveAura("aquatic form");

    return TRUE;
}



NextAction** CastRegrowthAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastRejuvenationAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastRegrowthOnPartyAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastRejuvenationOnPartyAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}



NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), NULL), CastSpellAction::getPrerequisites());
}
