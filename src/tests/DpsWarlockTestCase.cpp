#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarlockActionFactory.h"

using namespace ai;


class DpsWarlockTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( DpsWarlockTestCase );
      CPPUNIT_TEST( combatVsMelee );
      CPPUNIT_TEST( summonPet );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarlockActionFactory(ai), "dps", NULL);
    }

protected:
 	void combatVsMelee()
	{
        tick(); 
        addAura("corruption");
        tick(); 
        addAura("curse of agony");
        
        tickWithLowHealth(49);

        tick(); 

		tickWithTargetLowHealth(19);
		
		ai->itemCounts["soulstone"] = 2;
		spellAvailable("drain soul");
		tickWithTargetLowHealth(19);

        assertActions(">corruption>curse of agony>drain life>shoot>drain soul");
	}

    void summonPet()
    {
        tickWithNoPet();

        assertActions(">summon imp");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarlockTestCase );
