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
	RepeatingAction(PlayerbotAIFacade* const ai) : Action(ai) {}

	virtual ~RepeatingAction()
	{
		destroyed++;
	}

    void Execute() { executed++; }
    const char* getName() {return "RepeatingAction"; }

    NextAction* getNextAction() { return new NextAction("RepeatingAction", 1.0f); }

	static int destroyed;
    static int executed;
};

int RepeatingAction::destroyed = 0;
int RepeatingAction::executed = 0;

class TriggeredAction : public Action
{
public:
	TriggeredAction(PlayerbotAIFacade* const ai) : Action(ai) { fired = false; }
	virtual ~TriggeredAction() {}

	void Execute() { fired = TRUE; }
    const char* getName() {return "TriggeredAction"; }

	static int fired;
};

int TriggeredAction::fired = 0;

class TestTrigger : public Trigger
{
public:
	TestTrigger(PlayerbotAIFacade* const ai) : Trigger(ai) {count = 0;}
	virtual BOOL IsActive() 
	{
		return ++count==3;
	}
    NextAction* getNextAction() { return new NextAction("TriggeredAction", 10.0f); }

private:
	int count;
};

class TestMultiplier : public Multiplier
{
public:
    TestMultiplier() : Multiplier() { asked = 0; }
    float GetValue(Action* action) { return asked = 5.0f; }

    static int asked;
};

int TestMultiplier::asked;

class TestStrategy : public Strategy
{
public:
    TestStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    BEGIN_NEXT_ACTIONS(1)
        NEXT_ACTION(0, "RepeatingAction", 1.0f)
    END_NEXT_ACTIONS(1)

    virtual void InitMultipliers(std::list<Multiplier*> &multipliers)
    {
        multipliers.push_back(new TestMultiplier());
    }

    virtual void InitTriggers(std::list<Trigger*> &triggers)
    {
        triggers.push_back(new TestTrigger(NULL));
    }
};

class TestActionFactory : public ActionFactory
{
public:
    TestActionFactory(PlayerbotAIFacade* const ai) : ActionFactory(ai) {}
    virtual Action* createAction(const char* name)
    {
        if (!strcmp("TriggeredAction", name))
            return new TriggeredAction(ai);

        if (!strcmp("RepeatingAction", name))
            return new RepeatingAction(ai);

        return NULL;
    }
    virtual Strategy* createStrategy(const char* name)
    {
        if (!strcmp("TestStrategy", name))
            return new TestStrategy(ai);

        return NULL;
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
		Engine engine(NULL, new TestActionFactory(NULL));
        engine.addStrategy("TestStrategy");
        engine.Init();

		for (int i=0; i<6; i++)
			engine.DoNextAction(NULL);

		CPPUNIT_ASSERT(TriggeredAction::fired);
        CPPUNIT_ASSERT(TestMultiplier::asked);
        CPPUNIT_ASSERT_EQUAL(5, RepeatingAction::executed);
        CPPUNIT_ASSERT_EQUAL(5, RepeatingAction::destroyed);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( EngineTestCase );
