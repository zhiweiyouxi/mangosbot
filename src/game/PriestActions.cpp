#include "pchdef.h"
#include "PriestActions.h"
#include "GenericActions.h"

using namespace ai;


NextAction** CastAbolishDiseaseAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease"), NULL), CastSpellAction::getAlternatives());
}

NextAction** CastAbolishDiseaseOnPartyAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease on party"), NULL), CastSpellAction::getAlternatives());
}

BOOL CastHolyNovaAction::isUseful() {
    return ai->GetPartyMinHealthPercent() <= 80;
}