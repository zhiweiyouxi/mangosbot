#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/paladin/PaladinActionFactory.h"

using namespace ai;


class DpsPaladinTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsPaladinTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new PaladinActionFactory(ai), "dps", NULL);

        addAura("retribution aura");
        addAura("seal of command");
        addAura("blessing of might");

		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0;
    }
 
protected:
    void buff()
    {
        removeAura("retribution aura");
        removeAura("blessing of might");
        removeAura("seal of command");
        removeAura("holy shield");
        
        tick();
        addAura("devotion aura");
        
        tick();
        tick();
        tick();
        addAura("seal of wisdom");

        tick();
        tick(); 
        addAura("blessing of kings");
                
        assertActions(">S:retribution aura>S:seal of command>S:seal of wisdom>S:seal of justice>S:blessing of might>S:blessing of kings");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsPaladinTestCase );
