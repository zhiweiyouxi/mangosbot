#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarriorActionFactory.h"

using namespace ai;


class RacialsTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( RacialsTestCase );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new WarriorActionFactory(ai), "tank", NULL);

		engine->addStrategy("racials");
		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0;
		
		addAura("battle shout");
		addAura("defensive stance");
    }
 
protected:
    void healing()
    {
		tickWithLowHealth(39);
		tickWithLowHealth(39);

		assertActions(">S:lifeblood>S:gift of the naaru");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( RacialsTestCase );
