#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericWarriorStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class TankWarriorTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TankWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new WarriorActionFactory(ai));
        engine->addStrategy("tank");
        engine->Init();

        // this buff is combat-only, so skip for most test cases
        ai->auras.push_back("battle shout");
        ai->rage = 20;
    }

    void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

protected:
    void interruptSpells() 
    {
        ai->distanceToEnemy = 0.0f; 
        ai->targetIsCastingNonMeleeSpell = true;
        engine->DoNextAction(NULL); // shield bash
        ai->targetIsCastingNonMeleeSpell = false;
        
        engine->DoNextAction(NULL); // rend

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">shield bash>defensive stance"));
    }
    void healing()
    {
        ai->distanceToEnemy = 0.0f; 
        ai->health = 1;
        engine->DoNextAction(NULL); // gift of the naaru
        engine->DoNextAction(NULL); // regrowth

        ai->health = 50;
        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // shield wall
        engine->DoNextAction(NULL); // shield block

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">lifeblood>gift of the naaru>defensive stance>shield wall>shield block"));
    }
    void buff()
    {
        ai->rage = 0;
        ai->auras.remove("battle shout");

        engine->Init();
        engine->DoNextAction(NULL); // battle stance
        engine->DoNextAction(NULL); // battle shout

        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // bloodrage
        engine->DoNextAction(NULL); // melee
        engine->DoNextAction(NULL); // battle shout

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>battle shout>defensive stance>reach melee>melee>bloodrage>rend"));

    }
    void pickNewTarget()
    {
        engine->removeStrategy("assist");
        engine->Init();

        ai->auras.push_back("defensive stance");

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        engine->DoNextAction(NULL); // reach melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>attack bigger threat>devastate"));

    }

    void warriorMustDemoralizeAttackers()
    {
        ai->auras.push_back("defensive stance");

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->attackerCount = 2;
        ai->rage = 41;
        engine->DoNextAction(NULL); // demoralizing shout
        engine->DoNextAction(NULL); // thunder clap
        engine->DoNextAction(NULL); // cleave
        engine->DoNextAction(NULL); // heroic strike

        ai->rage = 20;

        ai->attackerCount = 3;
        engine->DoNextAction(NULL); // challenging shout
        engine->DoNextAction(NULL); // rend

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>demoralizing shout>thunder clap>cleave>heroic strike>challenging shout>devastate"));
    }

    void warriorMustHoldAggro()
    {
        ai->spellCooldowns.remove("defensive stance");
        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->aggro = FALSE;
        engine->DoNextAction(NULL); // taunt
        ai->aggro = TRUE;
        
        engine->DoNextAction(NULL); // rend

        ai->aggro = FALSE;
        engine->DoNextAction(NULL); // battle stance
        engine->DoNextAction(NULL); // mocking blow
        ai->aggro = TRUE;
        
        ai->spellCooldowns.remove("defensive stance");
        engine->DoNextAction(NULL);
        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">defensive stance>reach melee>melee>taunt>devastate>battle stance>mocking blow>defensive stance>revenge"));
    }

    void combatVsMelee()
    {
        ai->distanceToEnemy = 15.0f; // enemy too far
        ai->rage = 11;
        
        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // melee

        engine->DoNextAction(NULL); // bloodrage
        engine->DoNextAction(NULL); // rend
        ai->spellCooldowns.remove("rend");
        ai->targetAuras.push_back("rend");

        ai->rage = 21;
        engine->DoNextAction(NULL); // devastate
        engine->DoNextAction(NULL); // revenge
        engine->DoNextAction(NULL); // sunder armor

        engine->DoNextAction(NULL); // disarm
        ai->spellCooldowns.remove("disarm");
        ai->targetAuras.push_back("disarm");

        ai->rage = 41;
        engine->DoNextAction(NULL); // heroic strike

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("disarm");
        ai->targetAuras.push_back("disarm");
        ai->spellCooldowns.remove("devastate");

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("sunder armor");
        ai->targetAuras.push_back("sunder armor");

        ai->spellCooldowns.remove("heroic strike");
        engine->DoNextAction(NULL); // heroic strike
        ai->rage = 20;

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">defensive stance>reach melee>melee>bloodrage>rend>devastate>revenge>sunder armor>disarm>heroic strike>melee>devastate>heroic strike"));
    }

    void revengeIfDodge()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee
        ai->spellCooldowns.remove("revenge");
        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // revenge


        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>defensive stance>revenge"));
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankWarriorTestCase );
