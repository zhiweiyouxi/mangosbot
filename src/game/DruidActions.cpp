#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

BOOL CastBearFormAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("bear form") && !ai->HasAura("dire bear form");
}

BOOL CastBearFormAction::isUseful()
{
    return CastSpellAction::isUseful() && !ai->HasAura("bear form") && !ai->HasAura("dire bear form");
}

NextAction** CastDireBearFormAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
}

BOOL CastDireBearFormAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("dire bear form");
}

BOOL CastDireBearFormAction::isUseful()
{
    return CastSpellAction::isUseful() && !ai->HasAura("dire bear form");
}

BOOL CastRejuvenationAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("lifeblood");
}

BOOL CastRejuvenationAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

BOOL CastRegrowthAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

BOOL CastCasterFormAction::Execute()
{
    if (ai->HasAura("dire bear form")) 
        ai->RemoveAura("dire bear form");
    if (ai->HasAura("bear form")) 
        ai->RemoveAura("bear form");
    if (ai->HasAura("cat form")) 
        ai->RemoveAura("cat form");
    if (ai->HasAura("travel form")) 
        ai->RemoveAura("travel form");

    return TRUE;
}


BOOL CastCasterFormAction::isUseful()
{
    return (ai->HasAura("dire bear form") || ai->HasAura("bear form") ||
        ai->HasAura("cat form") || ai->HasAura("travel form")); 
}

BOOL CastMaulAction::isPossible()
{
    return CastSpellAction::isPossible() && ai->GetDistanceToEnemy() <= ATTACK_DISTANCE;
}

BOOL CastSwipeAction::isPossible()
{
    return CastSpellAction::isPossible() && ai->GetDistanceToEnemy() <= ATTACK_DISTANCE;
}
