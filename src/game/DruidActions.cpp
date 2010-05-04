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

BOOL CastCasterFormAction::ExecuteResult()
{
    if (ai->HasAura("dire bear form")) 
        ai->RemoveAura("dire bear form");
    if (ai->HasAura("bear form")) 
        ai->RemoveAura("bear form");
    if (ai->HasAura("cat form")) 
        ai->RemoveAura("cat form");
	if (ai->HasAura("moonkin form")) 
		ai->RemoveAura("moonkin form");
    if (ai->HasAura("travel form")) 
        ai->RemoveAura("travel form");

    return TRUE;
}


BOOL CastCasterFormAction::isUseful()
{
    return (ai->HasAura("dire bear form") || ai->HasAura("bear form") ||
        ai->HasAura("cat form") || ai->HasAura("travel form") || ai->HasAura("moonkin form")); 
}

BOOL CastCatFormAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->HasAura("cat form");
}

BOOL CastCatFormAction::isUseful()
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

BOOL CastMoonkinFormAction::isPossible()
{
	return CastSpellAction::isPossible() && !ai->HasAura("moonkin form");
}

BOOL CastMoonkinFormAction::isUseful()
{
	return CastSpellAction::isUseful() && !ai->HasAura("moonkin form");
}
