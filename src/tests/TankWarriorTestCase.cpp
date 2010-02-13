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
        ai->spellCooldowns.push_back("revenge");
        ai->auras.push_back("battle shout");
    }

    void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

protected:
    void healing()
    {
        ai->distanceToEnemy = 0.0f; 
        ai->health = 1;
        engine->DoNextAction(NULL); // gift of the naaru
        engine->DoNextAction(NULL); // regrowth

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">lifeblood>gift of the naaru"));
    }
    void buff()
    {
        ai->auras.remove("battle shout");
        engine->Init();
        engine->DoNextAction(NULL); // battle shout

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee
        engine->DoNextAction(NULL); // battle shout

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">battle shout>reach melee>melee>heroic strike"));

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
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>attack bigger threat>defensive stance"));

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
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>demoralizing shout>heroic strike"));
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

        ai->aggro = FALSE;
        engine->DoNextAction(NULL); // taunt
        ai->aggro = TRUE;
        
        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>defensive stance>mocking blow>heroic strike>taunt>rend"));
    }

    void combatVsMelee()
    {
        ai->distanceToEnemy = 15.0f; // enemy too far
        
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // melee

        engine->DoNextAction(NULL); // defensive stance

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("rend");
        ai->targetAuras.push_back("rend");

        engine->DoNextAction(NULL); // heroic strike

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("disarm");
        ai->targetAuras.push_back("disarm");

        engine->DoNextAction(NULL); 
        ai->spellCooldowns.remove("sunder armor");
        ai->targetAuras.push_back("sunder armor");

        ai->distanceToEnemy = 0.0f; 
        ai->rage = 15;
        ai->spellCooldowns.remove("heroic strike");
        engine->DoNextAction(NULL); // heroic strike


        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>defensive stance>rend>heroic strike>disarm>sunder armor>heroic strike"));
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
