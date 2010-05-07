#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericDruidStrategy.h"

using namespace ai;


class CasterDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( CasterDruidTestCase );
    CPPUNIT_TEST( combat);
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
	CPPUNIT_TEST( curePoison );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "caster", NULL);

		addAura("moonkin form");
    }

protected:
    void combat()
    {
		removeAura("moonkin form");
		tick();
		addAura("moonkin form");

		tickInSpellRange();
		addTargetAura("faerie fire");

		tick();
		addTargetAura("insect swarm");

		tick();
		addTargetAura("moonfire");

        tick();
		tick();

		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("starfire");
		tickInSpellRange();

		tickWithAttackerCount(3);
        
        assertActions(">moonkin form>faerie fire>insect swarm>moonfire>starfire>wrath>entangling roots>flee>starfire>nature's grasp");
    }

    void healHimself()
    {
		tickInSpellRange();

		lowHealth(39);
		tickWithSpellUnavailable("gift of the naaru");
        tick();
		addAura("lifeblood");

        tick();
        tick();
        
        healthRestored();
        removeAura("lifeblood");
        
		tick(); 
		addAura("moonkin form");

		tickWithLowHealth(39);
		tickWithLowHealth(39);
        
        assertActions(">faerie fire>lifeblood>-moonkin form>regrowth>moonkin form>insect swarm>-moonkin form>rejuvenation");
    }

	void healOthers()
    {
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);

        assertActions(">-moonkin form>rejuvenation on party>regrowth on party");
    }

	void curePoison() 
	{
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("abolish poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("cure poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		assertActions(">abolish poison>abolish poison on party>cure poison>cure poison on party");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( CasterDruidTestCase );
