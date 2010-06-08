#include "pch.h"

#include "../game/playerbot/strategy/Action.h"
#include "../game/playerbot/strategy/ActionBasket.h"
#include "../game/playerbot/strategy/Queue.h"
#include "../game/playerbot/strategy/Trigger.h"
#include "../game/playerbot/strategy/Engine.h"
#include "../game/playerbot/strategy/GenericActions.h"

using namespace ai;

class NextActionTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( NextActionTestCase );
	CPPUNIT_TEST( array );
    CPPUNIT_TEST( clone );
    CPPUNIT_TEST( merge );
    CPPUNIT_TEST( cloneNull );
    CPPUNIT_TEST( mergeWithNull );
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
    void array()
    {
        NextAction** actions = NextAction::array(0, new NextAction("1", 1), NULL);
        CPPUNIT_ASSERT(!strcmp("1", actions[0]->getName()));
        CPPUNIT_ASSERT(!actions[1]);
        NextAction::destroy(actions);
    }

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
        NextAction::destroy(cloned);
	}

    void merge()
    {
        NextAction** left = NextAction::array(0, new NextAction("1", 1),  new NextAction("2", 2), NULL);
        NextAction** right = NextAction::array(0, new NextAction("3", 3), NULL);

        NextAction** merged = NextAction::merge(left, right);

        CPPUNIT_ASSERT(!merged[3]);
        CPPUNIT_ASSERT(!strcmp("1", merged[0]->getName()));
        CPPUNIT_ASSERT(!strcmp("2", merged[1]->getName()));
        CPPUNIT_ASSERT(!strcmp("3", merged[2]->getName()));

        // check memory
        NextAction::destroy(merged);
    }

    void cloneNull()
    {
        NextAction** cloned = NextAction::clone(NULL);
        CPPUNIT_ASSERT(!cloned);
    }

    void mergeWithNull()
    {
        NextAction** left = NextAction::array(0, new NextAction("1", 1), NULL);
        NextAction** merged = NextAction::merge(left, NULL);

        CPPUNIT_ASSERT(!merged[1]);
        CPPUNIT_ASSERT(!strcmp("1", merged[0]->getName()));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NextActionTestCase );
