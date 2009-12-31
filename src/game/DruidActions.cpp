#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

BOOL CastBearFormAction::isAvailable()
{
    return !ai->HasAura("bear form") && !ai->HasAura("dire bear form");
}