#include "pchdef.h"
#include "DruidActions.h"
#include "GenericActions.h"

using namespace ai;

bool CastCasterFormAction::ExecuteResult()
{
    spellManager->RemoveAura("dire bear form");
    spellManager->RemoveAura("bear form");
    spellManager->RemoveAura("cat form");
	spellManager->RemoveAura("moonkin form");
    spellManager->RemoveAura("travel form");
	spellManager->RemoveAura("aquatic form");
    return true;
}


NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), NULL), CastSpellAction::getPrerequisites());
}
