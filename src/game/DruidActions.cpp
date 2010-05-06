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


bool CastCatFormAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("cat form");
}

bool CastCatFormAction::isUseful()
{
    return CastSpellAction::isUseful() && !ai->HasAura("cat form");
}


NextAction** CastRakeAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), new NextAction("cat form"), NULL), CastDebuffSpellAction::getPrerequisites());
}

NextAction** CastCowerAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastBerserkAction::getPrerequisites()
{
    return NextAction::array(0, new NextAction("cat form"), NULL);
}

NextAction** CastTigersFuryAction::getPrerequisites()
{
    return NextAction::array(0, new NextAction("cat form"), NULL);
}

NextAction** CastClawAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
}

NextAction** CastMangleCatAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
}

NextAction** CastFerociousBiteAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
}

NextAction** CastRipAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
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

NextAction** CastCurePoisonAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastCurePoisonOnPartyAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}


NextAction** CastAbolishPoisonAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getPrerequisites()
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
