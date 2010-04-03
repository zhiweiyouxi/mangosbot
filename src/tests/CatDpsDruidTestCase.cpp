#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericDruidStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class CatDpsDruidTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CatDpsDruidTestCase );
    CPPUNIT_TEST( tooFarForSpells );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( intensiveHealing );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST( boost );
    CPPUNIT_TEST( cower );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new DruidActionFactory(ai));
        engine->addStrategy("dps");
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
        engine->DoNextAction(NULL); // cat form
        ai->spellCooldowns.remove("cat form");

        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        engine->DoNextAction(NULL); // reach melee
        engine->DoNextAction(NULL); // reach melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>attack least threat>cat form>reach melee"));

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
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach spell>faerie fire>cat form>reach melee>rake"));
    }

    void combatVsMelee()
    {
        engine->DoNextAction(NULL); // faerie fire
        
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("dire bear form");

        ai->distanceToEnemy = 15.0f; // enemy too far
        engine->DoNextAction(NULL); // reach melee

        ai->distanceToEnemy = 0.0f; 
        engine->DoNextAction(NULL); // rake
        engine->DoNextAction(NULL); // mangle

        ai->comboPoints = 5;
        engine->DoNextAction(NULL); // ferocious bite

        ai->comboPoints = 5;
        engine->DoNextAction(NULL); // rip
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>reach melee>rake>mangle>ferocious bite>rip"));
    }

    void healHimself()
    {
        ai->spellCooldowns.push_back("gift of the naaru");
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // cat form
        ai->auras.push_back("cat form");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 39;
        engine->DoNextAction(NULL); // life blood
        ai->auras.push_back("lifeblood");

        engine->DoNextAction(NULL); // caster form
        engine->DoNextAction(NULL); // regrowth
        
        ai->health = 100;
        ai->auras.remove("lifeblood");
        ai->spellCooldowns.remove("cat form");
        ai->spellCooldowns.push_back("rake");
        engine->DoNextAction(NULL); // cat form
        ai->auras.push_back("cat form");
        engine->DoNextAction(NULL); // melee
        
        ai->health = 39;
        engine->DoNextAction(NULL); // rejuvenation

        engine->DoNextAction(NULL); // melee

        ai->resetSpells(); // continue as began
        ai->spellCooldowns.push_back("mangle");
        ai->spellCooldowns.push_back("rake");
        ai->health = 70;
        ai->auras.remove("cat form");
        ai->spellCooldowns.remove("cat form");
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>lifeblood>-cat form>regrowth>cat form>mangle>-cat form>rejuvenation>cat form>claw"));
    }

    void intensiveHealing()
    {
        ai->auras.push_back("cat form");
        ai->auras.remove("rejuvenation");

        ai->distanceToEnemy = 0.0f; 
        ai->health = 39;
        ai->auras.remove("rejuvenation");
        engine->DoNextAction(NULL); // life blood
        engine->DoNextAction(NULL); // gift of the naaru
        ai->auras.push_back("lifeblood");

        ai->spellCooldowns.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        engine->DoNextAction(NULL); // caster form
        ai->spellCooldowns.remove("rejuvenation");
        ai->auras.remove("rejuvenation");
        engine->DoNextAction(NULL); // regrowth

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">lifeblood>gift of the naaru>-cat form>regrowth"));
    }

    void healOthers()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // dire bear form
        ai->auras.push_back("cat form");

        ai->partyMinHealth = 39;
        engine->DoNextAction(NULL); // caster form
        ai->auras.remove("cat form");
        ai->spellCooldowns.remove("cat form");
        engine->DoNextAction(NULL); // rejuvenation on party
        engine->DoNextAction(NULL); // regrowth on party

        ai->partyMinHealth = 100;

        ai->resetSpells();
        ai->auras.clear();
        engine->DoNextAction(NULL); // continue as usual with cat form
        engine->DoNextAction(NULL); // reach melee
        engine->DoNextAction(NULL); // rake 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>-cat form>rejuvenation on party>regrowth on party>cat form>reach melee>rake"));
    }

    void boost()
    {
        engine->addStrategy("boost");

        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // cat form
        ai->auras.push_back("cat form");

        ai->balancePercent = 1;
        engine->DoNextAction(NULL); // berserk
        engine->DoNextAction(NULL); // cat form
        engine->DoNextAction(NULL); // tiger's fury
        
        ai->balancePercent = 100;

        ai->resetSpells();
        ai->auras.clear();
        engine->DoNextAction(NULL); // continue as usual with cat form

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>berserk>tiger's fury>reach melee>rake"));
    }

    void cower()
    {
        engine->DoNextAction(NULL); // faerie fire
        engine->DoNextAction(NULL); // cat form
        ai->auras.push_back("cat form");

        ai->myAttackerCount = 2;
        ai->attackerCount = 3;
        engine->DoNextAction(NULL); // cower
        ai->myAttackerCount = 0;
        ai->attackerCount = 1;

        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">faerie fire>cat form>cower>attack least threat"));
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( CatDpsDruidTestCase );
