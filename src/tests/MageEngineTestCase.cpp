#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/MageEngine.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class MageEngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( MageEngineTestCase );
  CPPUNIT_TEST( combat );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade ai;

public:
	void setUp()
	{
	}

protected:
	void combat()
	{
		MageEngine engine(&ai);
		engine.Init();

        // enemy too close -> frost nova
        engine.DoNextAction(NULL);
        // flee
        engine.DoNextAction(NULL);
        // frostbolt
        engine.DoNextAction(NULL);
        ai.resetSpells();
        // repeat as enemy is close again :)
        engine.DoNextAction(NULL);
        
        CPPUNIT_ASSERT(!strcmp(ai.buffer.c_str(), ">spell:frost nova>flee>spell:frostbolt>spell:frost nova"));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageEngineTestCase );
