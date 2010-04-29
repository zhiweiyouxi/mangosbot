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
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();


public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "tank", NULL);
    }

protected:
    void pickNewTarget()
    {
        tick();
        tick();

		similateNoTarget();

		tick();

		assertActions(">faerie fire>dire bear form>attack bigger threat>feral charge - bear");

    }

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

		lowHealth(39);
		tickWithSpellUnavailable("gift of the naaru");
        tick();
		addAura("lifeblood");

        tick();
        tick();
        
        healthRestored();
        removeAura("lifeblood");
        
		tick(); 
		addAura("bear form");

		tickWithLowHealth(39);        
		tickWithLowHealth(39);
        
        assertActions(">faerie fire>dire bear form>melee>lifeblood>-dire bear form>regrowth>bear form>melee>-bear form>rejuvenation");
    }

    void intensiveHealing()
    {
        ai->auras.push_back("dire bear form");
        ai->auras.remove("rejuvenation");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 39;
        ai->auras.remove("rejuvenation");
        tick(); // life blood
        tick(); // gift of the naaru
        ai->auras.push_back("lifeblood");

        ai->spellCooldowns.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        ai->health = 1;
        tick(); // survival instincts
        ai->health = 39;
        tick(); // caster form
        tick(); // regrowth

        assertActions(">lifeblood>gift of the naaru>survival instincts>-dire bear form>regrowth");
    }

    void healOthers()
    {
        tick(); // faerie fire
        tick(); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->partyMinHealth = 39;
        tick(); // caster form
        tick(); // rejuvenation on party
        tick(); // regrowth on party

        ai->partyMinHealth = 100;

        ai->resetSpells();
        ai->auras.clear();
        tick(); // continue as usual with bear form

        assertActions(">faerie fire>dire bear form>-dire bear form>rejuvenation on party>regrowth on party>dire bear form");
    }
    void curePoison() 
    {
        tick(); // faerie fire
        tick(); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->aurasToDispel = DISPEL_POISON;
        tick(); // caster form
        tick(); // abolish poison
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_POISON;
        ai->spellCooldowns.remove("abolish poison");
        tick(); // abolish poison on party
        ai->partyAurasToDispel = 0;

        ai->aurasToDispel = DISPEL_POISON;
        tick(); // cure poison
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_POISON;
        ai->spellCooldowns.remove("cure poison");
        tick(); // cure poison on party
        ai->partyAurasToDispel = 0;

        ai->resetSpells();
        ai->auras.clear();
        tick(); // continue as usual with bear form

        assertActions(">faerie fire>dire bear form>-dire bear form>abolish poison>abolish poison on party>cure poison>cure poison on party>dire bear form");
    }
    void interruptSpells() 
    {
        tick(); // faerie fire
        tick(); // dire bear form
        ai->auras.push_back("dire bear form");
        
        ai->distanceToEnemy = 0.0f; 
        ai->targetIsCastingNonMeleeSpell = true;
        tick(); // bash
        ai->targetIsCastingNonMeleeSpell = false;

        tick(); // 

        assertActions(">faerie fire>dire bear form>bash>melee");
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( BearTankDruidTestCase );
