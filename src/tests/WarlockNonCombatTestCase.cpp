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

        assertActions(">demon skin>demon armor");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarlockNonCombatTestCase );
