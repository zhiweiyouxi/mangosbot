#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericWarriorStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class DpsWarriorTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DpsWarriorTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( warriorMustHoldAggro );
    CPPUNIT_TEST( warriorMustDemoralizeAttackers );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( execute );
    CPPUNIT_TEST( hamstring );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new WarriorActionFactory(ai));
        engine->addStrategy("dps");
        engine->Init();
        ai->spellCooldowns.push_back("revenge");
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
    void buff()
    {
        ai->auras.remove("battle shout");
        engine->Init();

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee
        engine->DoNextAction(NULL); // battle shout

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>battle shout>charge"));

    }
    void pickNewTarget()
    {
        engine->removeStrategy("assist");
        engine->Init();

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        engine->DoNextAction(NULL); // reach melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>attack least threat>melee"));

    }

    void warriorMustDemoralizeAttackers()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->attackerCount = 3;
        engine->DoNextAction(NULL); // demoralizing roar
        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>melee>demoralizing shout"));
    }

    void warriorMustHoldAggro()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->aggro = FALSE;
        engine->DoNextAction(NULL); // defensive stance
        engine->DoNextAction(NULL); // mocking blow
        ai->aggro = TRUE;
        
        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>melee>mocking blow>rend"));
    }

    void combatVsMelee()
    {
        ai->distanceToEnemy = 15.0f; // enemy too far
        engine->DoNextAction(NULL); // battle stance
        engine->DoNextAction(NULL); // charge

        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // melee

        ai->distanceToEnemy = 15.0f; // enemy again too far

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // melee

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("rend");
        ai->targetAuras.push_back("rend");

        ai->rage = 41;
        engine->DoNextAction(NULL); // bloodthirst

        engine->DoNextAction(NULL); // melee

        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // heroic strike
        ai->rage = 0;

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>melee>reach melee>melee>rend>bloodthirst>heroic strike>melee"));
    }

    void boost()
    {
        engine->addStrategy("boost");

        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // battle stance

        ai->balancePercent = 1;

        engine->DoNextAction(NULL); // death wish
        engine->DoNextAction(NULL); // berserker rage
        engine->DoNextAction(NULL); // 
        ai->balancePercent = 100;

        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>death wish>berserker rage>charge>melee"));
    }

    void execute()
    {
        engine->DoNextAction(NULL); // battle stance
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // charge

        ai->targetHealth = 24;
        engine->DoNextAction(NULL); // execute
        ai->targetHealth = 100;

        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>execute>melee"));
    }


    void hamstring()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->targetIsMoving = true;
        engine->DoNextAction(NULL); // battle stance
        engine->DoNextAction(NULL); // hamstring
        ai->spellCooldowns.remove("defensive stance");
        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle stance>charge>melee>hamstring>rend"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsWarriorTestCase );
