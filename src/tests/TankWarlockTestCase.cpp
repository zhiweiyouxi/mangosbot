#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warlock/WarlockActionFactory.h"

using namespace ai;


class TankWarlockTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( TankWarlockTestCase );
      CPPUNIT_TEST( summonPet );
      CPPUNIT_TEST( cc );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarlockActionFactory(ai), "tank", NULL);
    }

protected:

    void summonPet()
    {
        inventoryManager->itemCounts["soul shard"] = 2;
        tickWithNoPet();

		assertActions(">S:summon voidwalker");
    }

    void cc()
    {
        tickWithCcTarget();

        assertActions(">Cc:banish");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarlockTestCase );
