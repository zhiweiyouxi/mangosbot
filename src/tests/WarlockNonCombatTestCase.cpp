#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarlockActionFactory.h"
#include "../game/GenericWarlockNonCombatStrategy.h"

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

        assertActions(">demon skin>demon armor>create healthstone>create firestone>create spellstone");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarlockNonCombatTestCase );
