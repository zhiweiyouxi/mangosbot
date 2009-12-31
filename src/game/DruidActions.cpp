#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

BOOL CastBearFormAction::isAvailable()
{
    return CastSpellAction::isAvailable() && !ai->HasAura("bear form") && !ai->HasAura("dire bear form");
}

BOOL CastDireBearFormAction::isAvailable()
{
    return CastSpellAction::isAvailable() && !ai->HasAura("dire bear form");
}

BOOL CastRejuvenationAction::isAvailable()
{
    return CastSpellAction::isAvailable() && !ai->HasAura("life blood");
}

BOOL CastRejuvenationAction::isUseful()
{
    return ai->GetHealthPercent() <= 25;
}

BOOL CastRegrowthAction::isUseful()
{
    return ai->GetHealthPercent() <= 25;
}

void CastCasterFormAction::Execute()
{
    if (ai->HasAura("dire bear form")) 
        ai->RemoveAura("dire bear form");
    if (ai->HasAura("bear form")) 
        ai->RemoveAura("bear form");
    if (ai->HasAura("cat form")) 
        ai->RemoveAura("cat form");
    if (ai->HasAura("travel form")) 
        ai->RemoveAura("travel form");
}