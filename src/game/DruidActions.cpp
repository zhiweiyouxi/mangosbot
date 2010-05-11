#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

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


NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), NULL), CastSpellAction::getPrerequisites());
}
