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

		for (int i=0; i<6; i++)
			engine.DoNextAction(NULL);

        std::cout << ai.buffer;
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageEngineTestCase );
