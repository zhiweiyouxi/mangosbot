#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanActionFactory.h"

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
        addAura("earthliving weapon");
    }

protected:
    void healHimself()
    {
		tickWithLowHealth(45);
        tickWithLowHealth(45);
		tickWithLowHealth(35);
        tickWithLowHealth(35);
        
        tick();
        tickInMeleeRange();

        assertActions(">S:chain heal>S:lesser healing wave>S:riptide>S:healing wave>reach melee>melee");
    }

    void healOthers()
    {
        tickWithPartyLowHealth(45);
        tickWithPartyLowHealth(45);
        tickWithPartyLowHealth(35);
		tickWithPartyLowHealth(35);

        assertActions(">P:chain heal>P:lesser healing wave>P:riptide>P:healing wave");
    }

    void buff()
    {
        removeAura("water shield");

        tick(); 
        addAura("water shield");

        removeAura("earthliving weapon");
        tick(); 
        tick(); 
        tick(); 
        tick(); 
        addAura("earthliving weapon");

        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);
        tickWithAttackerCount(3);

        assertActions(">S:water shield>S:earthliving weapon>S:flametongue weapon>S:frostbrand weapon>S:rockbiter weapon>S:strength of earth totem>S:windfury totem>S:flametongue totem>S:mana spring totem");
    }

    void interruptSpell() 
    {
        tickWithTargetIsCastingNonMeleeSpell();
        
		assertActions(">T:wind shear");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( HealShamanTestCase );
