#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericDruidStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class BearTankDruidTestCase : public CPPUNIT_NS::TestFixture
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

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new DruidActionFactory(ai));
        engine->addStrategy("tank");
        engine->Init();
    }

    void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

protected:
    void pickNewTarget()
    {
        engine->removeStrategy("assist");
        engine->Init();

        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form

        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        engine->DoNextAction(NULL); // reach melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>attack bigger threat>reach melee"));

    }

    void bearFormIfDireNotAvailable()
    {
        engine->DoNextAction(NULL); // faerie fire
        ai->spellCooldowns.push_back("dire bear form");
        engine->DoNextAction(NULL); // bear form
        ai->auras.push_back("bear form");

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>bear form"));
    }

    void tooFarForSpells()
    {
        ai->distanceToEnemy = 49.0f;
        engine->DoNextAction(NULL); // reach spell
        ai->distanceToEnemy = 15.0f;

        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 4.0f;
        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach spell>faerie fire>dire bear form>reach melee>melee"));
    }

    void druidMustDemoralizeAttackers()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        
        ai->attackerCount = 3;
        ai->auras.remove("dire bear form");
        ai->spellCooldowns.remove("dire bear form");
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // demoralizing roar
        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>dire bear form>reach melee>demoralizing roar>melee"));
    }

    void druidMustHoldAggro()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        ai->aggro = FALSE;
        engine->DoNextAction(NULL); // growl
        ai->aggro = TRUE;
        engine->DoNextAction(NULL); // reach melee
        engine->DoNextAction(NULL); // melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>growl>reach melee>melee"));
    }

    void druidMustDoMauls()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        ai->distanceToEnemy = 15.0f; // enemy too far
        engine->DoNextAction(NULL); // reach melee
        engine->DoNextAction(NULL); // melee
    
        ai->distanceToEnemy = 0.0f; 
        ai->rage = 10;
        engine->DoNextAction(NULL); // maul
        ai->spellCooldowns.remove("maul");
        engine->DoNextAction(NULL); // maul
    
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>reach melee>melee>maul>maul"));
    }

    void combatVsMelee()
    {
        engine->DoNextAction(NULL); // faerie fire
        
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->distanceToEnemy = 15.0f; // enemy too far
        engine->DoNextAction(NULL); // reach melee
        engine->DoNextAction(NULL); // melee

        ai->distanceToEnemy = 0.0f; 
        ai->rage = 10;
        engine->DoNextAction(NULL); // maul

        ai->rage = 15;
        engine->DoNextAction(NULL); // swipe

        ai->rage = 0;
        engine->DoNextAction(NULL); // melee
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>reach melee>melee>maul>swipe>melee"));
    }

    void healHimself()
    {
        ai->spellCooldowns.push_back("gift of the naaru");

        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 39;
        engine->DoNextAction(NULL); // life blood
        ai->auras.push_back("lifeblood");

        engine->DoNextAction(NULL); // caster form
        engine->DoNextAction(NULL); // regrowth
        
        ai->health = 100;
        ai->auras.remove("lifeblood");
        engine->DoNextAction(NULL); // bear form
        ai->auras.push_back("bear form");
        engine->DoNextAction(NULL); // melee
        
        ai->health = 39;
        engine->DoNextAction(NULL); // rejuvenation

        engine->DoNextAction(NULL); // melee

        ai->resetSpells(); // continue as began
        ai->health = 70;
        ai->auras.remove("dire bear form");
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>lifeblood>-dire bear form>regrowth>bear form>melee>-bear form>rejuvenation>faerie fire>dire bear form"));
    }

    void intensiveHealing()
    {
        ai->auras.push_back("dire bear form");
        ai->auras.remove("rejuvenation");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 39;
        ai->auras.remove("rejuvenation");
        engine->DoNextAction(NULL); // life blood
        engine->DoNextAction(NULL); // gift of the naaru
        ai->auras.push_back("lifeblood");

        ai->spellCooldowns.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        ai->health = 1;
        engine->DoNextAction(NULL); // survival instincts
        ai->health = 39;
        engine->DoNextAction(NULL); // caster form
        engine->DoNextAction(NULL); // regrowth

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">lifeblood>gift of the naaru>survival instincts>-dire bear form>regrowth"));
    }

    void healOthers()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->partyMinHealth = 39;
        engine->DoNextAction(NULL); // caster form
        engine->DoNextAction(NULL); // rejuvenation on party
        engine->DoNextAction(NULL); // regrowth on party

        ai->partyMinHealth = 100;

        ai->resetSpells();
        ai->auras.clear();
        engine->DoNextAction(NULL); // continue as usual with bear form

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>-dire bear form>rejuvenation on party>regrowth on party>dire bear form"));
    }
    void curePoison() 
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->aurasToDispel = DISPEL_POISON;
        engine->DoNextAction(NULL); // caster form
        engine->DoNextAction(NULL); // abolish poison
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_POISON;
        ai->spellCooldowns.remove("abolish poison");
        engine->DoNextAction(NULL); // abolish poison on party
        ai->partyAurasToDispel = 0;

        ai->aurasToDispel = DISPEL_POISON;
        engine->DoNextAction(NULL); // cure poison
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_POISON;
        ai->spellCooldowns.remove("cure poison");
        engine->DoNextAction(NULL); // cure poison on party
        ai->partyAurasToDispel = 0;

        ai->resetSpells();
        ai->auras.clear();
        engine->DoNextAction(NULL); // continue as usual with bear form

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>-dire bear form>abolish poison>abolish poison on party>cure poison>cure poison on party>dire bear form"));
    }
    void interruptSpells() 
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");
        
        ai->distanceToEnemy = 0.0f; 
        ai->targetIsCastingNonMeleeSpell = true;
        engine->DoNextAction(NULL); // bash
        ai->targetIsCastingNonMeleeSpell = false;

        engine->DoNextAction(NULL); // 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>dire bear form>bash>melee"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( BearTankDruidTestCase );
