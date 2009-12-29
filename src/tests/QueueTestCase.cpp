#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Engine.h"

using namespace ai;

class QueueTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( QueueTestCase );
	CPPUNIT_TEST( queueMustHaveOrder );
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void queueMustHaveOrder()
	{
		CastSpellAction action1(NULL, "1");
        CastSpellAction action2(NULL, "2");
        CastSpellAction action3(NULL, "3");

		Queue q;
		q.Push(new ActionBasket(&action1, 0.5f));
		q.Push(new ActionBasket(&action2, 0.7f));
		q.Push(new ActionBasket(&action3, 0.3f));

		CPPUNIT_ASSERT(q.Pop() == &action2);
		CPPUNIT_ASSERT(q.Pop() == &action1);
		CPPUNIT_ASSERT(q.Pop() == &action3);
		CPPUNIT_ASSERT(q.Pop() == NULL);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( QueueTestCase );
