#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/FrostMageStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class MageEngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( MageEngineTestCase );
  CPPUNIT_TEST( combatVsCaster );
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

        Engine engine(ai, new MageActionFactory(ai));
        engine.addStrategy("frost mage");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->spellCooldowns.remove("frostbolt");
        engine.DoNextAction(NULL);
        ai->spellCooldowns.remove("frostbolt");
        engine.DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">frostbolt>frostbolt>frostbolt"));
    }

	void combatVsMelee()
	{
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new MageActionFactory(ai));
        engine.addStrategy("frost mage");
        engine.Init();

        engine.DoNextAction(NULL); // frostbolt
        
        ai->distanceToEnemy = 0.0f; // enemy too close
        engine.DoNextAction(NULL); // frost nova
        
        engine.DoNextAction(NULL); // flee
        
        ai->distanceToEnemy = 15.0f; 
        ai->spellCooldowns.remove("frostbolt");
        
        engine.DoNextAction(NULL); // frostbolt
        ai->spellCooldowns.remove("frostbolt");

        engine.DoNextAction(NULL); // frostbolt
                
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">frostbolt>frost nova>flee>frostbolt>frostbolt"));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageEngineTestCase );
