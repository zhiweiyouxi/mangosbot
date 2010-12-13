#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/priest/PriestActionFactory.h"

using namespace ai;


class DpsPriestTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsPriestTestCase );
    CPPUNIT_TEST( combat );
    CPPUNIT_TEST_SUITE_END();


public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new PriestActionFactory(ai), "dps", NULL);

        addAura("power word: fortitude");
        addAura("divine spirit");
        addAura("inner fire");
        addPartyAura("power word: fortitude");
        addPartyAura("divine spirit");
    }

protected:
    void combat()
    {
        tick(); // shadowform
        addAura("shadowform");

        tick(); // shadow word: pain
        tick(); // devouring plague
        tick(); // mind blast
        tick(); // shoot

        // heal if need
        tickWithLowHealth(1); // shirld
        tickWithLowHealth(1); // -shadowform
        tickWithLowHealth(1); // greater heal
        
		assertActions(">S:shadowform>T:devouring plague>T:shadow word: pain>T:mind blast>T:shoot>-shadowform>S:power word: shield>S:greater heal");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsPriestTestCase );
