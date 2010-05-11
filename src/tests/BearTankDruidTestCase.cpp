#include "pch.h"
#include "EngineTestBase.h"
#include "../game/DruidActionFactory.h"

using namespace ai;

class BearTankDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( BearTankDruidTestCase );
    CPPUNIT_TEST( tooFarForSpells );
    CPPUNIT_TEST( druidMustDoMauls );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( druidMustHoldAggro );
    CPPUNIT_TEST( druidMustDemoralizeAttackers );
    CPPUNIT_TEST( bearFormIfDireNotAvailable );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( intensiveHealing );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( curePoison );
    CPPUNIT_TEST( interruptSpells );
	CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();


public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "bear", NULL);

		addAura("thorns");
    }

protected:
    void bearFormIfDireNotAvailable()
    {
        tick(); 
        
		tickWithSpellUnavailable("dire bear form");

        assertActions(">faerie fire>bear form");
    }

    void tooFarForSpells()
    {
		tickOutOfSpellRange();

        tick(); 
        tick(); 
		addAura("dire bear form");

        tick(); 
        
		tickInMeleeRange();

        assertActions(">reach spell>faerie fire>dire bear form>feral charge - bear>melee");
    }

    void druidMustDemoralizeAttackers()
    {
        tick(); 
        tick(); 

		spellAvailable("dire bear form"); // aura not yet applied

		tickWithAttackerCount(3);
		addAura("dire bear form");
		tickWithAttackerCount(3);

		tickInMeleeRange();
        
		tick(); 

        assertActions(">faerie fire>dire bear form>dire bear form>reach melee>demoralizing roar>melee");
    }

    void druidMustHoldAggro()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickWithNoAggro();

        tick();
        tick();

        assertActions(">faerie fire>dire bear form>growl>feral charge - bear>melee");
    }

    void druidMustDoMauls()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickInMeleeRange();

		tickWithRage(40);
		tickWithRage(40);
        
		tickWithSpellAvailable("maul");
    
        assertActions(">faerie fire>dire bear form>melee>mangle (bear)>maul>melee");
    }

    void combatVsMelee()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickOutOfMeleeRange();
		tick();
		
		tickOutOfMeleeRange();
        tick();

		tickWithRage(40);

		tickWithRage(50);

        tickWithRage(40);
        
        assertActions(">faerie fire>dire bear form>feral charge - bear>melee>reach melee>melee>mangle (bear)>swipe>maul");
    }

    void healHimself()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickInMeleeRange();

		tickWithLowHealth(59);
		tickWithLowHealth(59);

        tick();
		addAura("bear form");
        tick();
                
		tickWithLowHealth(39);
		tickWithLowHealth(39);
        
        assertActions(">faerie fire>dire bear form>melee>-dire bear form>rejuvenation>bear form>melee>-bear form>regrowth");
    }

    void intensiveHealing()
    {
        addAura("dire bear form");
		tickWithLowHealth(1);

        assertActions(">survival instincts");
    }

    void healOthers()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickWithPartyLowHealth(59);
		tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(39);

        assertActions(">faerie fire>dire bear form>-dire bear form>rejuvenation on party>regrowth on party");
    }
    void curePoison() 
    {
        tick();
        tick();
        addAura("dire bear form");

		tickWithAuraToDispel(DISPEL_POISON);
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("abolish poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);
		
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("cure poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

        assertActions(">faerie fire>dire bear form>-dire bear form>abolish poison>abolish poison on party>cure poison>cure poison on party");
    }
    void interruptSpells() 
    {
        tick();
        tick();
        addAura("dire bear form");
        
		tickInMeleeRange();

		tickWithTargetIsCastingNonMeleeSpell();

        assertActions(">faerie fire>dire bear form>melee>bash");
    }
	void buff() 
	{
		removeAura("thorns");
		tick();
		
		tick();

		assertActions(">thorns>faerie fire");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( BearTankDruidTestCase );
