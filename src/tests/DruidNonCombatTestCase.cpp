#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericDruidStrategy.h"

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

        assertActions(">mark of the wild>mark of the wild on party");
    }

	void resurrect()
	{
		tickWithDeadPartyMember();

		assertActions(">revive on party");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidNonCombatTestCase );
