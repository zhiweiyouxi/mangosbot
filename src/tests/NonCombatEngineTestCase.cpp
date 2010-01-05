#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class NonCombatEngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase );
  CPPUNIT_TEST( followMaster );
  CPPUNIT_TEST( stay );
  CPPUNIT_TEST( eatDrink );
  CPPUNIT_TEST( assist );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
	void setUp()
	{
	}

protected:
    void followMaster()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("follow");
        engine.Init();

        engine.DoNextAction(NULL);
        std::cout << ai->buffer;
        
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">follow"));
    }

    void stay()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.Init();

        engine.DoNextAction(NULL);
        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay"));
    }

    void assist()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.addStrategy("assist");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->myAttackerCount = 0;
        engine.DoNextAction(NULL);
        ai->myAttackerCount = 1;

        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay>attack least threat"));
    }

    void eatDrink()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("follow");
        engine.Init();

        ai->health = 1;
        ai->mana = 1;
        engine.DoNextAction(NULL);
        ai->auras.push_back("eat");
        engine.DoNextAction(NULL);
        ai->auras.push_back("drink");
        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">eat>drink"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase );
