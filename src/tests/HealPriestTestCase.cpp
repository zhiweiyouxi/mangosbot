#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/priest/PriestActionFactory.h"

using namespace ai;


class HealPriestTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( HealPriestTestCase );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( nonCombat );
    CPPUNIT_TEST( dispel );
    CPPUNIT_TEST( fade );
    CPPUNIT_TEST( enemyTooClose );
	CPPUNIT_TEST( racials );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new PriestActionFactory(ai), "heal", NULL);

        addAura("power word: fortitude");
        addAura("divine spirit");
        addAura("inner fire");
        addPartyAura("power word: fortitude");
        addPartyAura("divine spirit");
    }

protected:
    void healHimself()
    {
        addPartyAura("power word: fortitude");

		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);

		tick();

		tickWithLowHealth(59);

		tickWithSpellAvailable("shoot");

		assertActions(">S:power word: shield>S:greater heal>S:renew>S:heal>S:lesser heal>T:shoot>S:flash heal>T:shoot");
    }

	void racials()
	{
		engine->addStrategy("racials");
		addPartyAura("power word: fortitude");

		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithLowHealth(39);

		tick();

		tickWithLowHealth(59);

		tickWithSpellAvailable("shoot");

		assertActions(">S:lifeblood>S:gift of the naaru>S:power word: shield>S:greater heal>S:renew>S:heal>S:lesser heal>T:shoot>S:flash heal>T:shoot");
	}

    void nonCombat()
    {
        engine->removeStrategy("heal");
        engine->addStrategy("nc");

        addPartyAura("power word: fortitude");

		tickWithLowHealth(1);

		tickWithDeadPartyMember();

		assertActions(">S:flash heal>P:resurrection");
    }

    void healOthers()
    {
        tick(); // shoot

		tickWithPartyLowHealth(1);
		tickWithPartyLowHealth(1);
		tickWithPartyLowHealth(1);
		tickWithPartyLowHealth(1);
		tickWithPartyLowHealth(1);

		tickWithSpellAvailable("shoot");

		tickWithPartyLowHealth(59);

        tickWithSpellAvailable("shoot"); // shoot


		assertActions(">T:shoot>P:power word: shield>P:greater heal>P:renew>P:heal>P:lesser heal>T:shoot>P:flash heal>T:shoot");
    }

    void buff()
    {
        engine->removeStrategy("heal");
        engine->addStrategy("nc");
        
		removeAura("power word: fortitude");
        removeAura("divine spirit");
        removeAura("inner fire");
        removePartyAura("power word: fortitude");
        removePartyAura("divine spirit");

        tick(); // power word: fortitude
        addAura("power word: fortitude");

        tickWithSpellAvailable("power word: fortitude"); // power word: fortitude on party

        tick(); // inner fire

        tick(); // divine spirit
        addAura("divine spirit");

		tickWithSpellAvailable("divine spirit");

		assertActions(">S:power word: fortitude>S:divine spirit>S:inner fire>P:power word: fortitude>P:divine spirit");
    }

    void fade()
    {
        tick(); 
        
		tickWithMyAttackerCount(2);

		tickWithSpellAvailable("shoot");

		assertActions(">T:shoot>S:fade>T:shoot");
    }

    void enemyTooClose()
    {
        tick(); 

		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("shoot");
		tickInSpellRange();

		assertActions(">T:shoot>S:fade>flee>T:shoot");
    }

    void dispel() 
    {
        tick(); // shoot

		tickWithAuraToDispel(DISPEL_MAGIC);

		spellAvailable("dispel magic");
		tickWithPartyAuraToDispel(DISPEL_MAGIC);

		tickWithAuraToDispel(DISPEL_DISEASE);

		spellAvailable("abolish disease");
		tickWithPartyAuraToDispel(DISPEL_DISEASE);

		tickWithAuraToDispel(DISPEL_DISEASE);

		spellAvailable("cure disease");
		tickWithPartyAuraToDispel(DISPEL_DISEASE);

        tickWithSpellAvailable("shoot");

		assertActions(">T:shoot>S:dispel magic>P:dispel magic>S:abolish disease>P:abolish disease>S:cure disease>P:cure disease>T:shoot");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( HealPriestTestCase );
