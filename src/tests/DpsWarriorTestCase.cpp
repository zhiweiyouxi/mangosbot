#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarriorActionFactory.h"
#include "../game/GenericWarriorStrategy.h"

using namespace ai;


class DpsWarriorTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( execute );
    CPPUNIT_TEST( hamstring );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorActionFactory(ai), "dps", NULL);

		spellUnavailable("revenge");
        addAura("battle shout");
        ai->rage = 20;
    }

protected:
    void buff()
    {
        removeAura("battle shout");

        tickInSpellRange(); // reach melee
		tickInMeleeRange();
        tick();

        assertActions(">battle stance>battle shout>charge");

    }

    void warriorMustDemoralizeAttackers()
    {
        tickInMeleeRange(); // melee

		tickWithAttackerCount(3);

        assertActions(">battle stance>demoralizing shout");
    }

    void warriorMustHoldAggro()
    {
        tickInMeleeRange(); // melee

		tickWithNoAggro();
		tickWithNoAggro();
        
        tick(); 

        assertActions(">battle stance>mocking blow>charge>melee");
    }

    void combatVsMelee()
    {
		tickInSpellRange();
		tickInSpellRange();

		tickInMeleeRange();

		tickInSpellRange();

		tickInMeleeRange();

        tick(); 
        
		spellAvailable("rend");
        addTargetAura("rend");

        tickWithRage(41);
        tickWithRage(41);

        tick(); // bloodrage

        assertActions(">battle stance>charge>melee>reach melee>melee>rend>bloodthirst>heroic strike>bloodrage");
    }

    void boost()
    {
        engine->addStrategy("boost");

        tickInMeleeRange(); // battle stance

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);
		tickWithBalancePercent(1);

        tick(); // melee

        assertActions(">battle stance>death wish>berserker rage>charge>melee");
    }

    void execute()
    {
        tickInMeleeRange(); // battle stance

		tickWithTargetLowHealth(24);

        tick(); // melee

        assertActions(">battle stance>execute>charge");
    }


    void hamstring()
    {
		tickInMeleeRange(); // reach melee

		tickWithTargetIsMoving();
		tickWithTargetIsMoving();
        
        tickWithSpellAvailable("defensive stance"); // melee

        assertActions(">battle stance>hamstring>charge>melee");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarriorTestCase );
