#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarriorActionFactory.h"
#include "../game/GenericWarriorStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class TankWarriorTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( TankWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorActionFactory(ai), "tank", NULL);

        // this buff is combat-only, so skip for most test cases
        addAura("battle shout");
        ai->rage = 20;
		ai->distanceToEnemy = 0.0f; 
    }

protected:
    void interruptSpells() 
    {
		tickWithTargetIsCastingNonMeleeSpell();
        
        tick(); // rend

        assertActions(">shield bash>defensive stance");
    }

    void healing()
    {
		tickWithLowHealth(24);
		tickWithLowHealth(24);

        tickWithLowHealth(50); // defensive stance
        tickWithLowHealth(50); // shield wall
        tickWithLowHealth(50); // shield block

		tickWithLowHealth(4); 
		tickWithLowHealth(4); 

        assertActions(">lifeblood>gift of the naaru>defensive stance>shield wall>shield block>last stand>intimidating shout");
    }

    void buff()
    {
        ai->rage = 0;
        removeAura("battle shout");

        tickInSpellRange(); // battle stance
        tickInSpellRange(); // battle shout

        tickInSpellRange(); // defensive stance
        tickInSpellRange(); // reach melee
        
		
        tickInMeleeRange(); // bloodrage
        tick(); // melee
        tick(); // battle shout

        assertActions(">battle stance>battle shout>defensive stance>reach melee>melee>bloodrage>rend");

    }

    void warriorMustDemoralizeAttackers()
    {
        addAura("defensive stance");

        tick(); // melee

        ai->rage = 41;

		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);

        ai->rage = 21;
		tickWithAttackerCount(3);
		
		tick();

        assertActions(">melee>shockwave>demoralizing shout>thunder clap>cleave>shield slam>challenging shout>devastate");
    }

    void warriorMustHoldAggro()
    {
        tickWithSpellAvailable("defensive stance");
        tick(); // melee

		tickWithNoAggro();
        
        tick(); // rend
        
        tick();

        assertActions(">defensive stance>melee>taunt>devastate>revenge");
    }

    void combatVsMelee()
    {
        ai->distanceToEnemy = 15.0f; // enemy too far
        ai->rage = 11;
        
        tick(); // defensive stance
        tick(); // reach melee
        ai->distanceToEnemy = 0.0f; 
        tick(); // melee

        tick(); // bloodrage
        tick(); // rend
        spellAvailable("rend");
        addTargetAura("rend");

        ai->rage = 21;
        tick(); // devastate
        tick(); // revenge
        tick(); // sunder armor

		ai->rage = 31;
		tick();

        tick(); // disarm
        spellAvailable("disarm");
        addTargetAura("disarm");

        ai->rage = 41;
        tick(); // heroic strike

        tick(); 
        spellAvailable("disarm");
        addTargetAura("disarm");
        spellAvailable("devastate");

        tick(); 
        spellAvailable("sunder armor");
        addTargetAura("sunder armor");

		tick(); 

        spellAvailable("heroic strike");
        tick(); 
        ai->rage = 20;

        assertActions(">defensive stance>reach melee>melee>bloodrage>rend>devastate>revenge>sunder armor>shield slam>disarm>heroic strike>melee>devastate>slam>heroic strike");
    }

    void revengeIfDodge()
    {
        tick(); // melee
        spellAvailable("revenge");
        tick(); // defensive stance
        tick(); // revenge


        assertActions(">melee>defensive stance>revenge");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarriorTestCase );
