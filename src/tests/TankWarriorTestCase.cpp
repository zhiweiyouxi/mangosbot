#include "pch.h"

#include "EngineTestBase.h"
#include "../game/WarriorActionFactory.h"
#include "../game/GenericWarriorStrategy.h"

#include "MockAiManagerRegistry.h"

using namespace ai;


class TankWarriorTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( TankWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( healing );
	CPPUNIT_TEST( snare );
    CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        EngineTestBase::setUp();
        setupEngine(new WarriorActionFactory(ai), "tank", NULL);

        // this buff is combat-only, so skip for most test cases
        addAura("battle shout");
        statsManager->rage[MockedTargets::GetSelf()] = 20;
		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0;
    }

protected:
    void interruptSpells() 
    {
		tickWithTargetIsCastingNonMeleeSpell();
        
        tick(); // rend

        assertActions(">T:shield bash>S:defensive stance");
    }

    void healing()
    {
        tickWithLowHealth(50); // defensive stance
        tickWithLowHealth(50); // shield wall
        tickWithLowHealth(50); // shield block

		tickWithLowHealth(4); 
		tickWithLowHealth(4); 

		assertActions(">S:defensive stance>T:shield wall>S:shield block>S:last stand>T:intimidating shout");
    }

    void buff()
    {
        statsManager->rage[MockedTargets::GetSelf()] = 0;
        removeAura("battle shout");

        tickInSpellRange(); // battle stance
        tickInSpellRange(); // battle shout

        tickInSpellRange(); // defensive stance
        tickInSpellRange(); // reach melee
        
		
        tickInMeleeRange(); // bloodrage
        tick(); // melee
        tick(); // battle shout

		assertActions(">S:battle stance>S:battle shout>S:defensive stance>reach melee>melee>S:bloodrage>T:rend");

    }

    void warriorMustDemoralizeAttackers()
    {
        addAura("defensive stance");

        tick(); // melee

        statsManager->rage[MockedTargets::GetSelf()] = 41;

		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);

        statsManager->rage[MockedTargets::GetSelf()] = 21;
		tickWithAttackerCount(3);
		
		tick();

        assertActions(">melee>T:shockwave>T:demoralizing shout>T:thunder clap>T:cleave>T:shield slam>T:challenging shout>T:devastate");
    }

    void warriorMustHoldAggro()
    {
        tickWithSpellAvailable("defensive stance");
        tick(); // melee

		tickWithNoAggro();
        
        tick(); // rend
        
        tick();

		assertActions(">S:defensive stance>melee>T:taunt>T:devastate>T:revenge");
    }

    void combatVsMelee()
    {
		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f; // enemy too far
        statsManager->rage[MockedTargets::GetSelf()] = 11;
        
        tick(); // defensive stance
        tick(); // reach melee
        moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f; 
        tick(); // melee

        tick(); // bloodrage
        tick(); // rend
        spellAvailable("rend");
        addTargetAura("rend");

        statsManager->rage[MockedTargets::GetSelf()] = 21;
        tick(); // devastate
        tick(); // revenge
        tick(); // sunder armor

		statsManager->rage[MockedTargets::GetSelf()] = 31;
		tick();

        tick(); // disarm
        spellAvailable("disarm");
        addTargetAura("disarm");

        statsManager->rage[MockedTargets::GetSelf()] = 41;
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
        statsManager->rage[MockedTargets::GetSelf()] = 20;

        addAura("sword and board");
        tickWithSpellAvailable("shield slam");

		assertActions(">S:defensive stance>reach melee>melee>S:bloodrage>T:rend>T:devastate>T:revenge>T:sunder armor>T:shield slam>T:disarm>T:heroic strike>melee>T:devastate>T:slam>T:heroic strike>T:shield slam");
    }

    void revengeIfDodge()
    {
        tick(); // melee
        spellAvailable("revenge");
        tick(); // defensive stance
        tick(); // revenge

		assertActions(">melee>S:defensive stance>T:revenge");
    }

	void snare()
	{
		tick();
		tick();
		tickWithTargetIsMoving();
		
		assertActions(">S:defensive stance>melee>T:concussion blow");
	}
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarriorTestCase );
