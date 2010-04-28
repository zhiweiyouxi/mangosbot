#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericPaladinStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class TankPaladinTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TankPaladinTestCase );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( paladinMustHoldAggro );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST( stopEnemyMove );
    CPPUNIT_TEST( buff );
	CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new PaladinActionFactory(ai));
        engine->addStrategy("tank");
        engine->Init();

        ai->auras.push_back("devotion aura");
        ai->auras.push_back("seal of justice");
        ai->auras.push_back("blessing of kings");
        ai->auras.push_back("righteous fury");

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
        ai->auras.remove("righteous fury");
        engine->DoNextAction(NULL);

        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>righteous fury"));
    }

    void healing()
    {
        ai->distanceToEnemy = 0.0f; 
        
        ai->health = 50;
        engine->DoNextAction(NULL); 
        
        ai->health = 30;
        engine->DoNextAction(NULL); // gift of the naaru
        engine->DoNextAction(NULL); // regrowth

        engine->DoNextAction(NULL); 
        engine->DoNextAction(NULL); 
        ai->health = 100;
        engine->DoNextAction(NULL); 

		ai->health = 20;
		engine->DoNextAction(NULL); 
		ai->spellCooldowns.remove("lay on hands");
		ai->health = 100;
		ai->partyMinHealth = 20;
		engine->DoNextAction(NULL); 
		ai->partyMinHealth = 100;

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">flash of light>lifeblood>divine shield>holy light>gift of the naaru>divine protection>lay on hands>lay on hands on party"));
    }
  
    void pickNewTarget()
    {
        engine->removeStrategy("assist");
        engine->Init();

        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->myAttackerCount = 0;
        ai->haveTarget = FALSE;
        engine->DoNextAction(NULL); // attack bigger threat
        ai->myAttackerCount = 1;
        ai->haveTarget = TRUE;
        engine->DoNextAction(NULL); // reach melee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>attack bigger threat>judgement of light"));

    }

    void paladinMustHoldAggro()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->attackerCount = 2;
        engine->DoNextAction(NULL); // holy wrath
        engine->DoNextAction(NULL); // consecration
		engine->DoNextAction(NULL); // consecration

        ai->aggro = FALSE;
        engine->DoNextAction(NULL); 
		engine->DoNextAction(NULL); 
        ai->aggro = TRUE;

        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>holy wrath>avenger's shield>consecration>hand of reckoning>exorcism>judgement of justice"));
    }

    void combatVsMelee()
    {
        ai->distanceToEnemy = 15.0f; // enemy too far
        
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0.0f; 
        
        engine->DoNextAction(NULL); // melee
        engine->DoNextAction(NULL); // 

		ai->targetHealth = 24;
		engine->DoNextAction(NULL); // finish them

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>judgement of light>hammer of wrath"));
    }

    void stopEnemyMove()
    {
        engine->DoNextAction(NULL); // reach melee
        ai->distanceToEnemy = 0;
        engine->DoNextAction(NULL); // melee

        ai->targetIsMoving = true;
        engine->DoNextAction(NULL); // hammer of justice
		engine->DoNextAction(NULL); // judgement of justice
		ai->targetIsMoving = false;
        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">reach melee>melee>hammer of justice>judgement of justice>judgement of light"));
    }

	void interruptSpells() 
	{
		ai->distanceToEnemy = 0.0f; 
		ai->targetIsCastingNonMeleeSpell = true;
		engine->DoNextAction(NULL);
		ai->targetIsCastingNonMeleeSpell = false;

		engine->DoNextAction(NULL);

		std::cout << ai->buffer;
		CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">hammer of justice>melee"));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankPaladinTestCase );
