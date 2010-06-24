#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warlock/WarlockActionFactory.h"

using namespace ai;


class WarlockNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( WarlockNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarlockActionFactory(ai), "nc", NULL);
    }

protected:
    void buff()
    {
		tickWithSpellUnavailable("demon armor");

		tickWithSpellAvailable("demon armor");
		tick();

		itemAvailable("soulstone", 2);
		tick();
		itemAvailable("healthstone", 1);

		tick();
		itemAvailable("firestone", 1);

		tick();
		itemAvailable("spellstone", 1);

		assertActions(">S:demon skin>S:demon armor>S:create healthstone>S:create firestone>S:create spellstone");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarlockNonCombatTestCase );
