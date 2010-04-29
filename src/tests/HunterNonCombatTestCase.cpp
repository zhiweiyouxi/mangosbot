#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericHunterStrategy.h"

using namespace ai;


class HunterNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( HunterNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( summonPet );
	CPPUNIT_TEST( buffIfPackUnavailable );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new HunterActionFactory(ai), "nc", NULL);

        ai->attackerCount = 0;
    }

protected:
    void buff()
    {
		tick();

		tickWithAttackerCount(1);
        
        assertActions(">aspect of the pack>aspect of the hawk");
    }

    void summonPet()
    {
        tickWithNoPet();
        
		tickWithPetLowHealth(0); // dead
		tickWithPetLowHealth(30);

		assertActions(">call pet>revive pet>mend pet");
	}        

    void buffIfPackUnavailable()
    {
        tickWithSpellUnavailable("aspect of the pack");

        assertActions(">aspect of the cheetah");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( HunterNonCombatTestCase );
