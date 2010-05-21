#include "pch.h"

#include "EngineTestBase.h"
#include "../game/ShamanActionFactory.h"
#include "../game/GenericShamanStrategy.h"

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
		addAura("earthliving weapon");
                        
		tick();

		assertActions(">S:earthliving weapon>S:water shield");
    }

	void ressurect()
	{
		tickWithDeadPartyMember();

		assertActions(">P:ancestral spirit");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( ShamanNonCombatTestCase );
