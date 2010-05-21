#include "pch.h"

#include "EngineTestBase.h"
#include "../game/HealShamanStrategy.h"
#include "../game/ShamanActionFactory.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class HealShamanTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( HealShamanTestCase );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( interruptSpell );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new ShamanActionFactory(ai), "heal", NULL);

        addAura("water shield");
    }

protected:
    void healHimself()
    {
		tickWithLowHealth(45);
		tickWithLowHealth(35);
        
        tick();
        tickInMeleeRange();

		assertActions(">S:chain heal>S:riptide>reach melee>melee");
    }

    void healOthers()
    {
        tickWithPartyLowHealth(45);
        tickWithPartyLowHealth(35);
		tickWithPartyLowHealth(35);

		assertActions(">P:chain heal>P:riptide>P:earth shield");
    }

    void buff()
    {
        removeAura("water shield");

        tick(); 
        addAura("water shield");

        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);

		assertActions(">S:water shield>S:strength of earth totem>S:windfury totem>S:flametongue totem>S:mana spring totem");
    }

    void interruptSpell() 
    {
        tickWithTargetIsCastingNonMeleeSpell();
        
		assertActions(">T:wind shear");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( HealShamanTestCase );
