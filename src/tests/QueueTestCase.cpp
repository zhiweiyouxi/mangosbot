#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Engine.h"
#include "../game/GenericActions.h"
#include "MockAiManagerRegistry.h"

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
		MockAiManagerRegistry mock;
		CastSpellAction action1(&mock, "1");
        CastSpellAction action2(&mock, "2");
        CastSpellAction action3(&mock, "3");

		Queue q;
		q.Push(new ActionBasket(new ActionNode(&action1, NULL, NULL, NULL), 0.5f));
		q.Push(new ActionBasket(new ActionNode(&action2, NULL, NULL, NULL), 0.7f));
		q.Push(new ActionBasket(new ActionNode(&action3, NULL, NULL, NULL), 0.3f));

		CPPUNIT_ASSERT(q.Pop()->getAction() == &action2);
		CPPUNIT_ASSERT(q.Pop()->getAction() == &action1);
		CPPUNIT_ASSERT(q.Pop()->getAction() == &action3);
		CPPUNIT_ASSERT(q.Pop() == NULL);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( QueueTestCase );
