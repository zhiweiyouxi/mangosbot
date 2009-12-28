#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
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

    ActionBasket** GetAfterActions() 
	{
		ActionBasket** actions = new ActionBasket*[1];
		actions[0] = new ActionBasket(new RepeatingAction(ai), 1.0f);
		return actions;
	}

	static int destroyed;
};

int RepeatingAction::destroyed = 0;

class TriggeredAction : public Action
{
public:
	TriggeredAction(PlayerbotAI* const ai) : Action(ai) { fired = false; }
	virtual ~TriggeredAction() {}

	void Execute() { fired = TRUE; }

	static int fired;
};

int TriggeredAction::fired = 0;

class TestTrigger : public Trigger
{
public:
	TestTrigger(PlayerbotAI* const ai) : Trigger(ai) {count = 0;}
	virtual BOOL IsActive() 
	{
		return ++count==3;
	}
	virtual ActionBasket** CreateHandlers() 
	{
		ActionBasket** actions = new ActionBasket*[1];
		actions[0] = new ActionBasket(new TriggeredAction(ai), 10.0f);
		return actions;
	}

private:
	int count;
};


class TestEngine : public Engine
{
public:
	TestEngine() : Engine(NULL, NULL, NULL) {}
	void Init() 
	{
		queue.Push(new ActionBasket(new RepeatingAction(NULL), 1.0f));
		triggers.push_back(new TestTrigger(NULL));
	}
};

class EngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( EngineTestCase );
  CPPUNIT_TEST( engineMustRepeatActions );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void engineMustRepeatActions()
	{
		TestEngine engine;
		engine.Init();

		for (int i=0; i<6; i++)
			engine.DoNextAction(NULL);

		CPPUNIT_ASSERT_EQUAL(RepeatingAction::destroyed, 5);
		CPPUNIT_ASSERT(TriggeredAction::fired);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( EngineTestCase );
