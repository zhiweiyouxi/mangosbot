#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Engine.h"
#include "../game/GenericActions.h"

using namespace ai;

class NextActionTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( NextActionTestCase );
	CPPUNIT_TEST( clone );
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void clone()
	{
		NextAction** actions = new NextAction*[3];
        actions[0] = new NextAction("1", 1);
        actions[1] = new NextAction("2", 2);
        actions[2] = NULL;

        NextAction** cloned = NextAction::clone(actions);

		CPPUNIT_ASSERT(!cloned[2]);
		CPPUNIT_ASSERT(!strcmp("1", cloned[0]->getName()));
        CPPUNIT_ASSERT(!strcmp("2", cloned[1]->getName()));

        // check memory
        delete actions[0]; delete actions[1]; delete actions;
        delete cloned[0]; delete cloned[1]; delete cloned;
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( NextActionTestCase );
