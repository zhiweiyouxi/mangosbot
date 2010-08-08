#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/mage/MageActionFactory.h"

using namespace ai;


class MageNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( MageNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new MageActionFactory(ai), "nc", NULL);
    }

protected:
    void buff()
    {
		tick();
        addAura("arcane intellect");

		tickWithSpellAvailable("arcane intellect");

        tick();
        tick();
        tick();
        addAura("mage armor");

		tickWithNoDrink();
		tickWithNoFood();

        assertActions(">S:arcane intellect>P:arcane intellect>S:mage armor>S:ice armor>S:frost armor>S:conjure water>S:conjure food");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageNonCombatTestCase );
