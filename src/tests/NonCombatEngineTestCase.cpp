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
  CPPUNIT_TEST( dpsAssist );
  CPPUNIT_TEST( tankNonCombat );
  CPPUNIT_TEST( loot );
  CPPUNIT_TEST( goaway );
  CPPUNIT_TEST( emote );
  CPPUNIT_TEST( passive );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
	void setUp()
	{
	}

protected:
    void goaway() 
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("goaway");
        engine.Init();

        ai->attackerCount = 0;
        engine.DoNextAction(NULL);
        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">goaway"));
    }
    
    void followMaster()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("follow");
        engine.Init();

        ai->attackerCount = 0;
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

    void dpsAssist()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.addStrategy("dps assist");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->myAttackerCount = 0;
        ai->haveTarget = FALSE;
        engine.DoNextAction(NULL);
        ai->myAttackerCount = 1;
        ai->haveTarget = TRUE;

        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay>attack least threat"));
    }

	void tankAssist()
	{
		ai = new MockPlayerbotAIFacade();

		Engine engine(ai, new ActionFactory(ai));
		engine.addStrategy("stay");
		engine.addStrategy("tank assist");
		engine.Init();

		engine.DoNextAction(NULL);
		ai->myAttackerCount = 0;
		ai->haveTarget = FALSE;
		engine.DoNextAction(NULL);
		ai->myAttackerCount = 1;
		ai->haveTarget = TRUE;

		std::cout << ai->buffer;

		CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay>attack bigger threat"));
	}
    void loot()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.addStrategy("loot");
        engine.Init();

        ai->lootAvailable = true;
        engine.DoNextAction(NULL);
        ai->lootAvailable = false;
        engine.DoNextAction(NULL);
        ai->myAttackerCount = 1;

        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">loot>stay"));
    }

    void tankNonCombat()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.addStrategy("tank assist");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->haveTarget = FALSE;
        ai->myAttackerCount = 0;
        engine.DoNextAction(NULL);
        ai->myAttackerCount = 1;
        ai->haveTarget = TRUE;

        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay>attack bigger threat"));
    }

    void eatDrink()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("food");
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

    void emote()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("emote");
        engine.Init();

        for (int i=0; i<100; i++)
            engine.DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(strstr(ai->buffer.c_str(), ">emote"));
    }

    void passive()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new ActionFactory(ai));
        engine.addStrategy("stay");
        engine.addStrategy("passive");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->myAttackerCount = 0;
        engine.DoNextAction(NULL);
        ai->myAttackerCount = 1;

        std::cout << ai->buffer;

        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">stay>stay"));
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase );
