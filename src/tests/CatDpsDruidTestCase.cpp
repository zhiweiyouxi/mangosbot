#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericDruidStrategy.h"

using namespace ai;


class CatDpsDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( CatDpsDruidTestCase );
    CPPUNIT_TEST( tooFarForSpells );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( intensiveHealing );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( cower );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "cat", NULL);

		addAura("cat form");
		spellUnavailable("faerie fire");
    }

protected:
    void tooFarForSpells()
    {
		removeAura("cat form");
		spellAvailable("faerie fire");

		tickOutOfSpellRange();
		tick();
        tick();
		addAura("cat form");
		
		tickOutOfMeleeRange();
		tickInMeleeRange();

        assertActions(">reach spell>faerie fire>cat form>reach melee>rake");
    }

    void combatVsMelee()
    {
		tickInMeleeRange();

		tick();

        tickWithComboPoints(5);
        tickWithComboPoints(5);
        
        assertActions(">rake>mangle (cat)>ferocious bite>rip");
    }

	void healHimself()
	{
		tickInMeleeRange();

		tickWithLowHealth(59);
		tickWithLowHealth(59);

		tick();
		addAura("cat form");
		tick();

		tickWithLowHealth(39);
		tickWithLowHealth(39);

		assertActions(">rake>-cat form>rejuvenation>cat form>mangle (cat)>-cat form>regrowth");
	}
	
    void intensiveHealing()
    {
		tickWithLowHealth(1);

        assertActions(">survival instincts");
    }

	void healOthers()
    {
		tickWithPartyLowHealth(59);
		tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(39);

        assertActions(">-cat form>rejuvenation on party>regrowth on party");
    }

    void boost()
    {
        engine->addStrategy("boost");

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);
		tick();

        assertActions(">berserk>tiger's fury>reach melee");
    }

    void cower()
    {
		tickWithMyAttackerCount(2);

		tickOutOfMeleeRange();
        assertActions(">cower>reach melee");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( CatDpsDruidTestCase );
