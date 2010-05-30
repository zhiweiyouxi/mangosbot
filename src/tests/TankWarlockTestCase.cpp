#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarlockActionFactory.h"

using namespace ai;


class TankWarlockTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( TankWarlockTestCase );
      CPPUNIT_TEST( summonPet );
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
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarlockTestCase );
