#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/MageActionFactory.h"
#include "../game/FrostMageStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class FrostMageTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( FrostMageTestCase );
  CPPUNIT_TEST( pickNewTarget );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST( dispel );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new MageActionFactory(ai));
        engine->addStrategy("frost");
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
 	void combatVsMelee()
	{
        engine->DoNextAction(NULL); // frostbolt
        ai->spellCooldowns.remove("frostbolt");
        
        ai->distanceToEnemy = 1;
        engine->DoNextAction(NULL); // frost nova
        engine->DoNextAction(NULL); // flee
        
        ai->distanceToEnemy = 15.0f; 
        ai->resetSpells();        
        engine->DoNextAction(NULL); // frostbolt                
        engine->DoNextAction(NULL); // shoot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">frostbolt>frost nova>flee>frostbolt>shoot"));
	}

    void pickNewTarget()
    {
        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        ai->resetSpells();
        engine->DoNextAction(NULL); // frostbolt

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">attack least threat>frostbolt"));

    }

    void dispel() 
    {
        engine->DoNextAction(NULL); // frostbolt

        ai->aurasToDispel = DISPEL_CURSE;
        engine->DoNextAction(NULL); // remove curse
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_CURSE;
        ai->spellCooldowns.remove("remove curse");
        engine->DoNextAction(NULL); // remove curse on party
        ai->partyAurasToDispel = 0;

        engine->DoNextAction(NULL); // shoot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">frostbolt>remove curse>remove curse on party>shoot"));
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( FrostMageTestCase );
