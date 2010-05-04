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
		tickWithLowHealth(1);
		tickWithLowHealth(1);

        tickWithLowHealth(50); // defensive stance
        tickWithLowHealth(50); // shield wall
        tickWithLowHealth(50); // shield block

        assertActions(">lifeblood>gift of the naaru>defensive stance>shield wall>shield block");
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

        ai->rage = 20;
		tickWithAttackerCount(3);
		
		tick();

        assertActions(">melee>demoralizing shout>thunder clap>cleave>heroic strike>challenging shout>devastate");
    }

    void warriorMustHoldAggro()
    {
        tickWithSpellAvailable("defensive stance");
        tick(); // melee

		tickWithNoAggro();
        
        tick(); // rend

		tickWithNoAggro();
		tickWithNoAggro();
        
        tickWithSpellAvailable("defensive stance");
        tick();

        assertActions(">defensive stance>melee>taunt>devastate>battle stance>mocking blow>defensive stance>revenge");
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
        ai->spellCooldowns.remove("rend");
        ai->targetAuras.push_back("rend");

        ai->rage = 21;
        tick(); // devastate
        tick(); // revenge
        tick(); // sunder armor

        tick(); // disarm
        ai->spellCooldowns.remove("disarm");
        ai->targetAuras.push_back("disarm");

        ai->rage = 41;
        tick(); // heroic strike

        tick(); 
        ai->spellCooldowns.remove("disarm");
        ai->targetAuras.push_back("disarm");
        ai->spellCooldowns.remove("devastate");

        tick(); 
        ai->spellCooldowns.remove("sunder armor");
        ai->targetAuras.push_back("sunder armor");

        ai->spellCooldowns.remove("heroic strike");
        tick(); // heroic strike
        ai->rage = 20;

        std::cout << ai->buffer;
        assertActions(">defensive stance>reach melee>melee>bloodrage>rend>devastate>revenge>sunder armor>disarm>heroic strike>melee>devastate>heroic strike");
    }

    void revengeIfDodge()
    {
        tick(); // melee
        ai->spellCooldowns.remove("revenge");
        tick(); // defensive stance
        tick(); // revenge


        assertActions(">melee>defensive stance>revenge");
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarriorTestCase );
