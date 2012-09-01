#include "pch.h"

#include "aitest.h"
#include "MockAiObjectContext.h"
#include "MockedAiObjectContextTestCase.h"
#include "../game/playerbot/strategy/generic/ChatCommandHandlerStrategy.h"

using namespace ai;


class DuelTestCase : public MockedAiObjectContextTestCase
{
  CPPUNIT_TEST_SUITE( DuelTestCase );
      CPPUNIT_TEST( accept );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(context = new MockAiObjectContext(ai, new AiObjectContext(ai), &ai->buffer), "default", "duel", NULL);
    }

protected:
    void accept()
    {
        trigger("duel requested");
        tick();

        assertActions(">S:accept duel");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DuelTestCase );
