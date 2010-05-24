#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericPaladinStrategy.h"

using namespace ai;


class PaladinNonCombatTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( PaladinNonCombatTestCase );
        CPPUNIT_TEST( buff );
		CPPUNIT_TEST( resurrect );
    CPPUNIT_TEST_SUITE_END();


public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new PaladinActionFactory(ai), "nc", NULL);

        statsManager->attackerCount = 0;
    }

protected:
    void buff()
    {
        tick();
        addAura("devotion aura");

		spellUnavailable("seal of justice");
		
		tickWithSpellUnavailable("seal of light");

		tickWithSpellAvailable("seal of justice");
        
		tickWithSpellAvailable("seal of light");
		addAura("seal of light");

        tick(); 
        addAura("blessing of sanctuary");
        
		tickWithSpellAvailable("blessing of kings");
		addPartyAura("blessing of kings");
        tick(); 

		assertActions(">S:devotion aura>S:seal of righteousness>S:seal of justice>S:seal of light>S:blessing of sanctuary>P:blessing of kings");
    }

	void resurrect()
	{
		tickWithDeadPartyMember();
		assertActions(">P:redemption");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( PaladinNonCombatTestCase );
