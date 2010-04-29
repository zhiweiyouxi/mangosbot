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
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( cower );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "dps", NULL);

		addAura("cat form");
		spellUnavailable("faerie fire");
    }

protected:
    void pickNewTarget()
    {
		similateNoTarget();

		tick();

		assertActions(">attack least threat>reach melee");
    }

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

		lowHealth(39);
		tickWithSpellUnavailable("gift of the naaru");
        tick();
		addAura("lifeblood");

        tick();
        tick();
        
        healthRestored();
        removeAura("lifeblood");
        
		tick(); 
		addAura("cat form");

		tickWithLowHealth(39);
		tickWithLowHealth(39);
        
        assertActions(">rake>lifeblood>-cat form>regrowth>cat form>mangle (cat)>-cat form>rejuvenation");
    }

    void intensiveHealing()
    {
		tickWithLowHealth(39);
        tickWithLowHealth(39);
        addAura("lifeblood");
        
		tickWithLowHealth(39);
		addAura("gift of the naaru");
        
		tickWithLowHealth(1);

        assertActions(">lifeblood>gift of the naaru>-cat form>survival instincts");
    }

	void healOthers()
    {
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);
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
