#include "pch.h"

#include "EngineTestBase.h"

using namespace ai;


class NonCombatEngineTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( NonCombatEngineTestCase );
  CPPUNIT_TEST( followMaster );
  CPPUNIT_TEST( stay );
  CPPUNIT_TEST( eatDrink );
  CPPUNIT_TEST( dpsAssist );
  CPPUNIT_TEST( tankAssist );
  CPPUNIT_TEST( loot );
  CPPUNIT_TEST( goaway );
  CPPUNIT_TEST( emote );
  CPPUNIT_TEST( passive );
  CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new ActionFactory(ai), "nc", NULL);
	}

protected:
    void goaway() 
    {
        engine->addStrategy("goaway");
		tickWithAttackerCount(0);
		assertActions(">goaway");
    }
    
    void followMaster()
    {
        engine->addStrategy("follow");

		tickWithAttackerCount(0);
		assertActions(">follow");
    }

    void stay()
    {
		engine->addStrategy("stay");

		tickWithAttackerCount(0);
		assertActions(">stay");
    }

    void dpsAssist()
    {
        engine->addStrategy("stay");
        engine->addStrategy("dps assist");

		tick();
		tickWithNoTarget();

		assertActions(">stay>attack least threat");
    }


	void tankAssist()
	{
		engine->addStrategy("stay");
		engine->addStrategy("tank assist");

		tick();
		tickWithNoTarget();

		assertActions(">stay>attack bigger threat");
	}
	
    void loot()
    {
		engine->addStrategy("stay");
		engine->addStrategy("loot");

		tickWithLootAvailable();
		tick();

        assertActions(">loot>stay");
    }

    void eatDrink()
    {
        engine->addStrategy("food");

		tickWithLowHealth(1);
		tickWithLowMana(1);

        assertActions(">eat>drink");
    }

    void emote()
    {
        engine->addStrategy("emote");

        for (int i=0; i<100; i++)
            tick();

        CPPUNIT_ASSERT(strstr(ai->buffer.c_str(), ">emote"));
    }

    void passive()
    {
        engine->addStrategy("stay");
        engine->addStrategy("passive");

        tick();
		tickWithNoTarget();

        assertActions(">stay>stay");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( NonCombatEngineTestCase );
