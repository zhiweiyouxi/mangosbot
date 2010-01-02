#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/DpsHunterStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class DpsHunterEngineTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( DpsHunterEngineTestCase );
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

        Engine engine(ai, new HunterActionFactory(ai));
        engine.addStrategy("frost DpsHunter");
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

        Engine engine(ai, new HunterActionFactory(ai));
        engine.addStrategy("dps hunter");
        engine.Init();

        engine.DoNextAction(NULL); // concussive shot
        engine.DoNextAction(NULL); // serpent sting
        ai->targetAuras.push_back("serpent sting");
        engine.DoNextAction(NULL); // auto shot
        
        ai->distanceToEnemy = 0.0f; // enemy too close
        engine.DoNextAction(NULL); // flee
                
        ai->distanceToEnemy = 15.0f; 
        ai->resetSpells();        
        engine.DoNextAction(NULL); // arcane shot

        ai->resetSpell("auto shot");        
        engine.DoNextAction(NULL); // auto shot
                
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">concussive shot>serpent sting>auto shot>flee>arcane shot>auto shot"));

	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsHunterEngineTestCase );
