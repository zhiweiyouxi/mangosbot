#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericHunterStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class HunterTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( HunterTestCase );
    //CPPUNIT_TEST( combatVsCaster );
    //CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade ai;

public:
    void setUp()
    {
        ai.resetSpells();
    }

protected:
    void combatVsCaster()
    {
        GenericHunterStrategy* strategy = new GenericHunterStrategy(&ai);
        Engine engine(&ai);
        engine.Init(strategy);

        engine.DoNextAction(NULL);
        ai.resetSpell("frostbolt");
        engine.DoNextAction(NULL);
        ai.resetSpell("frostbolt");
        engine.DoNextAction(NULL);

        std::cout << ai.buffer;
        CPPUNIT_ASSERT(!strcmp(ai.buffer.c_str(), ">frostbolt>frostbolt>frostbolt"));
    }

    void combatVsMelee()
    {
        GenericHunterStrategy* strategy = new GenericHunterStrategy(&ai);
        Engine engine(&ai);
        engine.Init(strategy);

        engine.DoNextAction(NULL); // frostbolt

        ai.distanceToEnemy = 0.0f; // enemy too close
        engine.DoNextAction(NULL); // frost nova

        engine.DoNextAction(NULL); // flee

        ai.distanceToEnemy = 100.0f; 
        ai.resetSpell("frostbolt");

        engine.DoNextAction(NULL); // frostbolt
        ai.resetSpell("frostbolt");

        engine.DoNextAction(NULL); // frostbolt

        std::cout << ai.buffer;
        CPPUNIT_ASSERT(!strcmp(ai.buffer.c_str(), ">frostbolt>frost nova>flee>frostbolt>frostbolt"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( HunterTestCase );
