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
	CPPUNIT_TEST( victoryRush );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorActionFactory(ai), "dps", NULL);

		spellUnavailable("revenge");
        addAura("battle shout");
        statsManager->rage[MockedTargets::GetSelf()] = 20;
    }

protected:
    void buff()
    {
        removeAura("battle shout");

        tickInSpellRange(); // reach melee
		tickInMeleeRange();
        tick();

		assertActions(">S:battle stance>S:battle shout>T:charge");

    }

    void warriorMustDemoralizeAttackers()
    {
        tickInMeleeRange(); // melee

		tickWithAttackerCount(3);

		assertActions(">S:battle stance>T:demoralizing shout");
    }

    void warriorMustHoldAggro()
    {
        tickInMeleeRange(); // melee

		tickWithNoAggro();
		tickWithNoAggro();
        
        tick(); 

		assertActions(">S:battle stance>T:mocking blow>T:charge>melee");
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

		assertActions(">S:battle stance>T:charge>melee>reach melee>melee>T:rend>T:bloodthirst>T:heroic strike>S:bloodrage");
    }

    void boost()
    {
        engine->addStrategy("boost");

        tickInMeleeRange(); // battle stance

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);
		tickWithBalancePercent(1);

        tick(); // melee

		assertActions(">S:battle stance>S:death wish>S:berserker rage>T:charge>melee");
    }

    void execute()
    {
        tickInMeleeRange(); // battle stance

		tickWithTargetLowHealth(24);

        tick(); // melee

		assertActions(">S:battle stance>T:execute>T:charge");
    }


    void hamstring()
    {
		tickInMeleeRange(); // reach melee

		tickWithTargetIsMoving();
		tickWithTargetIsMoving();
        
        tickWithSpellAvailable("defensive stance"); // melee

		assertActions(">S:battle stance>T:hamstring>T:charge>melee");
    }


	void victoryRush()
	{
		tickInMeleeRange(); 
		addAura("victory rush");
		
		tick();

		assertActions(">S:battle stance>T:victory rush");
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarriorTestCase );
