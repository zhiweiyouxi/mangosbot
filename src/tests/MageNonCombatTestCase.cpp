#include "pch.h"

#include "EngineTestBase.h"
#include "../game/MageActionFactory.h"
#include "../game/GenericMageNonCombatStrategy.h"

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

        assertActions(">arcane intellect>arcane intellect on party");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageNonCombatTestCase );
