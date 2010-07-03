#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidActionFactory.h"

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

		assertActions(">reach spell>T:faerie fire>S:cat form>reach melee>T:rake");
    }

    void combatVsMelee()
    {
		tickInMeleeRange();

		tick();

        tickWithComboPoints(5);
        tickWithComboPoints(5);
        
		assertActions(">T:rake>T:mangle (cat)>T:ferocious bite>T:rip");
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
        tickWithLowHealth(39);

        assertActions(">T:rake>-cat form>S:regrowth>S:cat form>T:mangle (cat)>-cat form>S:rejuvenation>S:healing touch");
	}
	
    void intensiveHealing()
    {
		tickWithLowHealth(1);

		assertActions(">S:survival instincts");
    }

	void healOthers()
    {
		tickWithPartyLowHealth(59);
		tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);

		assertActions(">-cat form>P:regrowth>P:rejuvenation>P:healing touch");
    }

    void boost()
    {
        engine->addStrategy("boost");

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);
		tick();

		assertActions(">S:berserk>S:tiger's fury>reach melee");
    }

    void cower()
    {
		tickWithMyAttackerCount(2);

		tickOutOfMeleeRange();
		assertActions(">S:cower>reach melee");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( CatDpsDruidTestCase );
