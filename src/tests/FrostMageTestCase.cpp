#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/mage/MageActionFactory.h"

using namespace ai;


class FrostMageTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( FrostMageTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( dispel );
  CPPUNIT_TEST( boost );
  CPPUNIT_TEST( interruptSpells );
  CPPUNIT_TEST( pull );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new MageActionFactory(ai), "frost", NULL);
    }

protected:
 	void combatVsMelee()
	{
        tick();
        spellAvailable("frostbolt");
        
		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("frostbolt");
		tickInSpellRange();
        tick();

		tickWithLowHealth(24);

		assertActions(">T:frostbolt>T:frost nova>flee>T:frostbolt>T:shoot>S:ice block");
	}

    void dispel() 
    {
        tick(); 

		tickWithAuraToDispel(DISPEL_CURSE);

		spellAvailable("remove curse");
		tickWithPartyAuraToDispel(DISPEL_CURSE);

        tick(); 

		assertActions(">T:frostbolt>S:remove curse>P:remove curse>T:shoot");
    }

    void boost() 
    {
        engine->addStrategy("boost");

        tick(); // frostbolt

		tickWithBalancePercent(1);

        spellAvailable("frostbolt");
        tick(); // frostbolt

        tick(); // shoot

		assertActions(">T:frostbolt>S:icy veins>T:frostbolt>T:shoot");
    }

    void interruptSpells() 
    {
		tickWithTargetIsCastingNonMeleeSpell();

        tick(); // frostbolt

        assertActions(">T:counterspell>T:frostbolt");
    }


    void pull() 
    {
        engine->addStrategy("pull");
        
        tickOutOfSpellRange();
        tickInSpellRange();
        tick();
        tick();

        assertActions(">reach spell>T:shoot>follow>co:-pull");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( FrostMageTestCase );
