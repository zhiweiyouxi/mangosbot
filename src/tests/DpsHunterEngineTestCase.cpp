#include "pch.h"

#include "EngineTestBase.h"
#include "../game/DpsHunterStrategy.h"

using namespace ai;

class DpsHunterEngineTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( DpsHunterEngineTestCase );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( summonPet );
  CPPUNIT_TEST( lowMana );
  CPPUNIT_TEST( boost );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new HunterActionFactory(ai), "dps", NULL);

        addAura("aspect of the hawk");
    }

protected:
 	void combatVsMelee()
	{
        removeAura("aspect of the hawk");
        
		tick();
        addAura("aspect of the hawk");

		tick();
        tick();
		tick();
		addTargetAura("serpent sting");
		
		tick();
		tick();

		tickInMeleeRange();
		tickInSpellRange();
        
		// resetSpells
		tickWithSpellUnavailable("aimed shot");

        tick();
		tickWithSpellAvailable("auto shot");
                
        assertActions(">aspect of the hawk>hunter's mark>black arrow>serpent sting>explosive shot>auto shot>flee>concussive shot>wyvern sting>arcane shot>auto shot");

	}

    void lowMana()
    {
        spellUnavailable("serpent sting");
        spellUnavailable("concussive shot"); 
        removeAura("aspect of the hawk");

		tickWithLowMana(30);
		tickWithLowMana(30);
        
		tick();

        assertActions(">aspect of the viper>viper sting>aspect of the hawk");

    }

    void summonPet()
    {
        tickWithNoPet();
        
		tickWithPetLowHealth(0); // dead
		tickWithPetLowHealth(30);

		assertActions(">call pet>revive pet>mend pet");
	}    


    void boost()
    {
        engine->addStrategy("boost");

		tick();
        spellUnavailable("serpent sting");

		tickWithBalancePercent(1);
		tickWithBalancePercent(1);

        assertActions(">hunter's mark>rapid fire>readyness");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsHunterEngineTestCase );
