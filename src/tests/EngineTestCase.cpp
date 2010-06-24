#include "pch.h"

#include "aitest.h"
#include "MockAiManagerRegistry.h"

using namespace ai;

class PrerequisiteAction : public Action
{
public:
    PrerequisiteAction(AiManagerRegistry* const ai) : Action(ai) {}
    virtual ~PrerequisiteAction() { destroyed = TRUE; }

    bool ExecuteResult() { executed++; return TRUE; }
    const char* getName() {return "PrerequisiteAction"; }

    static int executed;
    static int destroyed;
};

int PrerequisiteAction::executed = 0;
int PrerequisiteAction::destroyed = 0;

class AlternativeAction : public Action
{
public:
    AlternativeAction(AiManagerRegistry* const ai) : Action(ai) {}
    virtual ~AlternativeAction() {destroyed = TRUE;}

    bool ExecuteResult() { executed++; return TRUE; }
    const char* getName() {return "AlternativeAction"; }

    static int executed;
    static int destroyed;
};

int AlternativeAction::executed = 0;
int AlternativeAction::destroyed = 0;

class RepeatingAction : public Action
{
public:
	RepeatingAction(AiManagerRegistry* const ai) : Action(ai) {}

	virtual ~RepeatingAction()
	{
		destroyed++;
	}

    bool ExecuteResult() { executed++; return TRUE; }
    const char* getName() {return "RepeatingAction"; }
    bool isPossible() { return available; }

	static int destroyed;
    static int executed;
    static int available;
};

int RepeatingAction::available = TRUE;
int RepeatingAction::destroyed = 0;
int RepeatingAction::executed = 0;

class TriggeredAction : public Action
{
public:
	TriggeredAction(AiManagerRegistry* const ai) : Action(ai) { fired = false; }
	virtual ~TriggeredAction() {}

	bool ExecuteResult() { fired = TRUE; return TRUE; }
    const char* getName() {return "TriggeredAction"; }

	static int fired;
};

int TriggeredAction::fired = 0;

class TestTrigger : public Trigger
{
public:
	TestTrigger(AiManagerRegistry* const ai) : Trigger(ai) {count = 0;}
	virtual bool IsActive() 
	{
		return ++count==3;
	}

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
    TestStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    virtual const char* getName() { return "TestStrategy"; }

    virtual NextAction** getDefaultActions() { return NextAction::array(0, new NextAction("RepeatingAction", 1.0f), NULL); }

    virtual void InitMultipliers(std::list<Multiplier*> &multipliers)
    {
        multipliers.push_back(new TestMultiplier());
    }

    virtual void InitTriggers(std::list<TriggerNode*> &triggers)
    {
        triggers.push_back(new TriggerNode(
            new TestTrigger(ai), 
            NextAction::array(0, new NextAction("TriggeredAction", 10.0f), NULL)));
    }

    virtual ActionNode* createAction(const char* name)
    {
        if (!strcmp("TriggeredAction", name)) 
        {
            return new ActionNode (new TriggeredAction(ai),  
                /*P*/ NULL,
                /*A*/ NULL, 
                /*C*/ NULL);
        }
        else if (!strcmp("RepeatingAction", name)) 
        {
            return new ActionNode (new RepeatingAction(ai),  
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("AlternativeAction", 1.0f), NULL), 
                /*C*/ NextAction::array(0, new NextAction("RepeatingAction", 1.0f), NULL));
        }
        else if (!strcmp("AlternativeAction", name)) 
        {
            return new ActionNode (new AlternativeAction(ai),  
                /*P*/ NextAction::array(0, new NextAction("PrerequisiteAction", 1.0f), NULL),
                /*A*/ NULL, 
                /*C*/ NULL);
        }
        else if (!strcmp("PrerequisiteAction", name)) 
        {
            return new ActionNode (new PrerequisiteAction(ai),  
                /*P*/ NULL,
                /*A*/ NULL, 
                /*C*/ NULL);
        }
        else return NULL;
    }
};

class AnotherTestStrategy : public Strategy
{
public:
    AnotherTestStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}
    
    virtual const char* getName() { return "AnotherTestStrategy"; }
};

class TestActionFactory : public ActionFactory
{
public:
    TestActionFactory(AiManagerRegistry* const ai) : ActionFactory(ai) {}
    virtual Strategy* createStrategy(const char* name)
    {
        if (!strcmp("TestStrategy", name))
            return new TestStrategy(ai);

        if (!strcmp("AnotherTestStrategy", name))
            return new AnotherTestStrategy(ai);

        return NULL;
    }
};

class EngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( EngineTestCase );
      CPPUNIT_TEST( engineMustRepeatActions );
      CPPUNIT_TEST( addRemoveStrategies );
      CPPUNIT_TEST( listStrategies );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void engineMustRepeatActions()
	{
		MockAiManagerRegistry mock;
		Engine engine(&mock, new TestActionFactory(&mock));
        engine.addStrategy("TestStrategy");
        engine.Init();

		for (int i=0; i<6; i++)
			engine.DoNextAction(NULL);

		CPPUNIT_ASSERT(TriggeredAction::fired);
        CPPUNIT_ASSERT(TestMultiplier::asked);
        CPPUNIT_ASSERT_EQUAL(5, RepeatingAction::executed);
        CPPUNIT_ASSERT_EQUAL(5, RepeatingAction::destroyed);

        RepeatingAction::available = FALSE;
        engine.DoNextAction(NULL);
        engine.DoNextAction(NULL);
        CPPUNIT_ASSERT(AlternativeAction::executed);
        CPPUNIT_ASSERT(AlternativeAction::destroyed);
        CPPUNIT_ASSERT(PrerequisiteAction::executed);
        CPPUNIT_ASSERT(PrerequisiteAction::destroyed);
	}

    void addRemoveStrategies()
    {
		MockAiManagerRegistry mock;
        Engine engine(&mock, new TestActionFactory(&mock));
        engine.addStrategy("AnotherTestStrategy");
        engine.removeStrategy("AnotherTestStrategy");
        engine.Init();
        
        engine.addStrategy("TestStrategy");
        engine.Init();

        engine.DoNextAction(NULL);
        CPPUNIT_ASSERT(TriggeredAction::fired);
    }

    void listStrategies()
    {
		MockAiManagerRegistry mock;
        Engine engine(&mock, new TestActionFactory(&mock));
        engine.addStrategy("AnotherTestStrategy");
        engine.addStrategy("TestStrategy");
        engine.Init();

        std::string s = engine.ListStrategies();
        CPPUNIT_ASSERT(s == "Strategies: AnotherTestStrategy, TestStrategy");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( EngineTestCase );
