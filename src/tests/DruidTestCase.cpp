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
    CPPUNIT_TEST( tooFarForSpells );
    CPPUNIT_TEST( druidMustDoMauls );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( druidMustHoldAggro );
    CPPUNIT_TEST( druidMustDemoralizeAttackers );
    CPPUNIT_TEST( bearFormIfDireNotAvailable );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( intensiveHealing );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
    void setUp()
    {
    }

protected:
    void bearFormIfDireNotAvailable()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        ai->alreadyCast.push_back("dire bear form");
        engine.DoNextAction(NULL); // bear form
        ai->auras.push_back("bear form");

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>bear form"));
    }

    void tooFarForSpells()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        ai->distanceToEnemy = 70.0f;
        engine.DoNextAction(NULL); // reach spell
        ai->distanceToEnemy = 15.0f;

        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        engine.DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach spell>faerie fire>dire bear form>melee"));
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
        ai->auras.remove("dire bear form");
        ai->resetSpell("dire bear form");
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        engine.DoNextAction(NULL); // demoralizing roar
        engine.DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>dire bear form>demoralizing roar>melee"));
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
        ai->distanceToEnemy = 15.0f; // enemy too far
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

        ai->distanceToEnemy = 15.0f; // enemy too far
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

    void healHimself()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 1;
        engine.DoNextAction(NULL); // life blood
        ai->auras.push_back("lifeblood");

        engine.DoNextAction(NULL); // caster form
        engine.DoNextAction(NULL); // regrowth
        
        ai->health = 100;
        ai->auras.remove("lifeblood");
        engine.DoNextAction(NULL); // bear form
        ai->auras.push_back("bear form");
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
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>lifeblood>-dire bear form>regrowth>bear form>melee>-bear form>rejuvenation>faerie fire>dire bear form"));
    }

    void intensiveHealing()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        ai->auras.push_back("dire bear form");
        ai->auras.remove("rejuvenation");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 1;
        ai->auras.remove("rejuvenation");
        engine.DoNextAction(NULL); // life blood
        ai->auras.push_back("lifeblood");

        ai->alreadyCast.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        engine.DoNextAction(NULL); // caster form
        ai->alreadyCast.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        engine.DoNextAction(NULL); // regrowth

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">lifeblood>-dire bear form>regrowth"));
    }

    void healOthers()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        engine.DoNextAction(NULL); // faerie fire
        engine.DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->partyMinHealth = 1;
        engine.DoNextAction(NULL); // caster form
        engine.DoNextAction(NULL); // rejuvenation on party
        engine.DoNextAction(NULL); // regrowth on party

        ai->partyMinHealth = 100;

        ai->resetSpells();
        ai->auras.clear();
        engine.DoNextAction(NULL); // continue as usual with bear form

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>-dire bear form>rejuvenation on party>regrowth on party>dire bear form"));
    }

    void pickNewTarget()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        ai->attackerCount = 0;
        engine.DoNextAction(NULL); // attack bigger threat
        ai->attackerCount = 1;
        engine.DoNextAction(NULL); // as usual

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">attack bigger threat>faerie fire"));

    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidTestCase );
