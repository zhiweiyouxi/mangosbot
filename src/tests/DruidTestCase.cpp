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
    CPPUNIT_TEST( druidMustDoMauls );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( druidMustHoldAggro );
    CPPUNIT_TEST( druidMustDemoralizeAttackers );
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

    void druidMustDemoralizeAttackers()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        ai->attackerCount = 3;
        engine.DoNextAction(NULL); // demoralizing roar
        engine.DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>demoralizing roar>melee"));
    }

    void druidMustHoldAggro()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        engine.DoNextAction(NULL); // melee
        ai->aggro = FALSE;
        engine.DoNextAction(NULL); // growl
        ai->aggro = TRUE;
        engine.DoNextAction(NULL); // maul

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>melee>growl>melee"));
    }

    void druidMustDoMauls()
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
        ai->resetSpell("maul");
        engine.DoNextAction(NULL); // maul
    
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>melee>maul>maul"));
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
        
        ai->health = 1;
        engine.DoNextAction(NULL); // life blood
        ai->auras.push_back("life blood");

        engine.DoNextAction(NULL); // regrowth
        
        ai->health = 100;
        ai->auras.remove("life blood");
        engine.DoNextAction(NULL); // melee
        
        ai->health = 1;
        engine.DoNextAction(NULL); // rejuvenation

        engine.DoNextAction(NULL); // melee

        ai->resetSpells(); // continue as began
        ai->health = 70;
        ai->auras.remove("dire bear form");
        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>melee>maul>swipe>melee>life blood>regrowth>melee>rejuvenation>melee>faerie fire>dire bear form"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidTestCase );
