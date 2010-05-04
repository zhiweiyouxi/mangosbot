#include "pch.h"

#include "EngineTestBase.h"
#include "../game/MageActionFactory.h"
#include "../game/FrostMageStrategy.h"

using namespace ai;


class FrostMageTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( FrostMageTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( dispel );
  CPPUNIT_TEST( boost );
  CPPUNIT_TEST( interruptSpells );
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

        assertActions(">frostbolt>frost nova>flee>frostbolt>shoot");
	}

    void dispel() 
    {
        tick(); 

		tickWithAuraToDispel(DISPEL_CURSE);

		spellAvailable("remove curse");
		tickWithPartyAuraToDispel(DISPEL_CURSE);

        tick(); 

        assertActions(">frostbolt>remove curse>remove curse on party>shoot");
    }

    void boost() 
    {
        engine->addStrategy("boost");

        tick(); // frostbolt

		tickWithBalancePercent(1);

        spellAvailable("frostbolt");
        tick(); // frostbolt

        tick(); // shoot

        assertActions(">frostbolt>icy veins>frostbolt>shoot");
    }

    void interruptSpells() 
    {
		tickWithTargetIsCastingNonMeleeSpell();

        tick(); // frostbolt

        assertActions(">counterspell>frostbolt");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( FrostMageTestCase );
