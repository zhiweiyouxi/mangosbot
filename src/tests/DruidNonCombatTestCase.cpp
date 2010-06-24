#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidActionFactory.h"

using namespace ai;


class DruidNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DruidNonCombatTestCase );
    CPPUNIT_TEST( buff );
	CPPUNIT_TEST( resurrect );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "nc", NULL);
    }

protected:
    void buff()
    {
		tick();
		addAura("mark of the wild");
                
		tickWithSpellAvailable("mark of the wild");
        
		tick();

		assertActions(">S:mark of the wild>P:mark of the wild");
    }

	void resurrect()
	{
		tickWithDeadPartyMember();

		assertActions(">P:revive");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidNonCombatTestCase );
