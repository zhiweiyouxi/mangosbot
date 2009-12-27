#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Engine.h"

using namespace ai;

class RepeatingAction : public Action
{
public:
	RepeatingAction(PlayerbotAI* const ai) : Action(ai) {}

	virtual ~RepeatingAction()
	{
		destroyed++;
	}
	virtual Action** GetAfterActions() 
	{
		Action** actions = new Action*[1];
		actions[0] = new RepeatingAction(ai);
		return actions;
	}

	static int destroyed;
};

int RepeatingAction::destroyed = 0;

class TestEngine : public Engine
{
public:
	TestEngine() : Engine(NULL, NULL, NULL) {}
	void Init() 
	{
		queue.Push(new RepeatingAction(NULL), 1.0f);
	}
};

class AiTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( AiTestCase );
  CPPUNIT_TEST( queueMustHaveOrder );
  CPPUNIT_TEST( engineMustRepeatActions );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void queueMustHaveOrder()
	{
		Action action1(NULL);
		Action action2(NULL);
		Action action3(NULL);

		Queue q;
		q.Push(&action1, 0.5f);
		q.Push(&action2, 0.7f);
		q.Push(&action3, 0.3f);		
		
		CPPUNIT_ASSERT(q.Pop() == &action2);
		CPPUNIT_ASSERT(q.Pop() == &action1);
		CPPUNIT_ASSERT(q.Pop() == &action3);
		CPPUNIT_ASSERT(q.Pop() == NULL);
	}
	void engineMustRepeatActions()
	{
		TestEngine engine;
		engine.Init();

		for (int i=0; i<5; i++)
			engine.DoNextAction(NULL);

		CPPUNIT_ASSERT_EQUAL(RepeatingAction::destroyed, 5);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( AiTestCase );
