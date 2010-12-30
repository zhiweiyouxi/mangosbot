#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/mage/MageActionFactory.h"

using namespace ai;


class FireMageTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( FireMageTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( boost );
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
		addTargetAura("pyroblast");

        tick();
		addTargetAura("fireball");

		tick();
		tick();
        
		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("fire blast");
		spellAvailable("scorch");
		tickInSpellRange();
        tick();
        tick();

		tickWithLowHealth(24);

		assertActions(">T:pyroblast>T:fireball>T:fire blast>T:scorch>T:frost nova>flee>T:fire blast>T:scorch>T:shoot>S:ice block");
	}

    void boost() 
    {
        tick();
		tickWithBalancePercent(1);
        tick();

		assertActions(">T:pyroblast>S:combustion>T:fireball");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( FireMageTestCase );
