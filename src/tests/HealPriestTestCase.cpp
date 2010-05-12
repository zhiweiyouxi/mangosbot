#include "pch.h"

#include "EngineTestBase.h"
#include "../game/HealPriestStrategy.h"
#include "../game/PriestActionFactory.h"

#include "MockPlayerbotAIFacade.h"

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

        assertActions(">power word: shield>greater heal>renew>heal>lesser heal>shoot>flash heal>shoot");
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

		assertActions(">lifeblood>gift of the naaru>power word: shield>greater heal>renew>heal>lesser heal>shoot>flash heal>shoot");
	}

    void nonCombat()
    {
        engine->removeStrategy("heal");
        engine->addStrategy("nc");

        addPartyAura("power word: fortitude");

		tickWithLowHealth(1);

		tickWithDeadPartyMember();

        assertActions(">flash heal>resurrection on party");
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


        assertActions(">shoot>power word: shield on party>greater heal on party>renew on party>heal on party>lesser heal on party>shoot>flash heal on party>shoot");
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

        assertActions(">power word: fortitude>divine spirit>inner fire>power word: fortitude on party>divine spirit on party");
    }

    void fade()
    {
        tick(); 
        
		tickWithMyAttackerCount(2);

		tickWithSpellAvailable("shoot");

        assertActions(">shoot>fade>shoot");
    }

    void enemyTooClose()
    {
        tick(); 

		tickInMeleeRange();
		tickInMeleeRange();

		spellAvailable("shoot");
		tickInSpellRange();

        assertActions(">shoot>fade>flee>shoot");
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

        assertActions(">shoot>dispel magic>dispel magic on party>abolish disease>abolish disease on party>cure disease>cure disease on party>shoot");
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( HealPriestTestCase );
