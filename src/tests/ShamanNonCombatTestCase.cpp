#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/shaman/ShamanActionFactory.h"

using namespace ai;


class ShamanNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( ShamanNonCombatTestCase );
    CPPUNIT_TEST( buff );
	CPPUNIT_TEST( ressurect );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new ShamanActionFactory(ai), "nc", NULL);
    }

protected:
    void buff()
    {
		tick();

		assertActions(">S:water shield");
    }

	void ressurect()
	{
		tickWithDeadPartyMember();

		assertActions(">P:ancestral spirit");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ShamanNonCombatTestCase );
