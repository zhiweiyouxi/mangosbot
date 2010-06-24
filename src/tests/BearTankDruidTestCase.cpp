#include "pch.h"
#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidActionFactory.h"

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

		assertActions(">T:faerie fire>S:bear form");
    }

    void tooFarForSpells()
    {
		tickOutOfSpellRange();

        tick(); 
        tick(); 
		addAura("dire bear form");

        tick(); 
        
		tickInMeleeRange();

		assertActions(">reach spell>T:faerie fire>S:dire bear form>T:feral charge - bear>melee");
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

		assertActions(">T:faerie fire>S:dire bear form>S:dire bear form>reach melee>T:demoralizing roar>melee");
    }

    void druidMustHoldAggro()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickWithNoAggro();

        tick();
        tick();

		assertActions(">T:faerie fire>S:dire bear form>T:growl>T:feral charge - bear>melee");
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
    
		assertActions(">T:faerie fire>S:dire bear form>melee>T:mangle (bear)>T:maul>melee");
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
        
        assertActions(">T:faerie fire>S:dire bear form>T:feral charge - bear>melee>reach melee>melee>T:mangle (bear)>T:swipe>T:maul");
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
        
		assertActions(">T:faerie fire>S:dire bear form>melee>-dire bear form>S:rejuvenation>S:bear form>melee>-bear form>S:regrowth");
    }

    void intensiveHealing()
    {
        addAura("dire bear form");
		tickWithLowHealth(1);

		assertActions(">S:survival instincts");
    }

    void healOthers()
    {
        tick();
        tick();
        addAura("dire bear form");

		tickWithPartyLowHealth(59);
		tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(39);

		assertActions(">T:faerie fire>S:dire bear form>-dire bear form>P:rejuvenation>P:regrowth");
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

		assertActions(">T:faerie fire>S:dire bear form>-dire bear form>S:abolish poison>P:abolish poison>S:cure poison>P:cure poison");
    }
    void interruptSpells() 
    {
        tick();
        tick();
        addAura("dire bear form");
        
		tickInMeleeRange();

		tickWithTargetIsCastingNonMeleeSpell();

        assertActions(">T:faerie fire>S:dire bear form>melee>T:bash");
    }
	void buff() 
	{
		removeAura("thorns");
		tick();
		
		tick();

		assertActions(">S:thorns>T:faerie fire");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( BearTankDruidTestCase );
