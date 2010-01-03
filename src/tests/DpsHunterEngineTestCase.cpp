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
  CPPUNIT_TEST( pickNewTarget );
  CPPUNIT_TEST( combatVsMelee );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
	void setUp()
	{
	}

protected:
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

        ai->resetSpell("arcane shot");        
        engine.DoNextAction(NULL); // arcane shot
        ai->resetSpell("auto shot");        
        engine.DoNextAction(NULL); // auto shot
                
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">serpent sting>arcane shot>auto shot>flee>concussive shot>arcane shot>auto shot"));

	}

    void pickNewTarget()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new HunterActionFactory(ai));
        engine.addStrategy("dps hunter");
        engine.Init();

        ai->alreadyCast.push_back("auto shot");
        ai->alreadyCast.push_back("serpent sting");
        ai->alreadyCast.push_back("concussive shot"); // this will not be available as we do not have any target
        ai->myAttackerCount = 0;
        engine.DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        ai->resetSpells();
        engine.DoNextAction(NULL); // concussive shot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">attack least threat>serpent sting"));

    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsHunterEngineTestCase );
