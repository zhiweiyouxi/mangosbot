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