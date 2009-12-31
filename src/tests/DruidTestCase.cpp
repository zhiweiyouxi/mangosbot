#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericDruidStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class DruidTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DruidTestCase );
    //CPPUNIT_TEST( combatVsCaster );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
    void setUp()
    {
    }

protected:
    void combatVsCaster()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.Init();

        engine.DoNextAction(NULL);
        ai->resetSpell("frostbolt");
        engine.DoNextAction(NULL);
        ai->resetSpell("frostbolt");
        engine.DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">frostbolt>frostbolt>frostbolt"));
    }

    void combatVsMelee()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->distanceToEnemy = 100.0f; // enemy too far
        engine.DoNextAction(NULL); // melee

        ai->distanceToEnemy = 0.0f; 
        ai->rage = 10;
        engine.DoNextAction(NULL); // maul

        ai->rage = 15;
        engine.DoNextAction(NULL); // swipe

        ai->rage = 0;
        engine.DoNextAction(NULL); // melee
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>melee>maul>swipe>melee"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidTestCase );
