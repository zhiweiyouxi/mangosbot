#include "pch.h"

#include "EngineTestBase.h"
#include "../game/MageActionFactory.h"
#include "../game/FireMageStrategy.h"

using namespace ai;


class FireMageTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( FireMageTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new MageActionFactory(ai), "fire", NULL);
    }

protected:
 	void combatVsMelee()
	{
        tick();
        spellAvailable("fireball");
        
		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("fireball");
		tickInSpellRange();
        tick();

		tickWithLowHealth(24);

		assertActions(">T:fireball>T:frost nova>flee>T:fireball>T:shoot>S:ice block");
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( FireMageTestCase );
