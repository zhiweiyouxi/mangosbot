#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericDruidStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class DruidNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DruidNonCombatTestCase );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
    void setUp()
    {
    }

protected:
    void healOthers()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("follow");
        engine.addStrategy("druid non combat");
        engine.Init();

        ai->partyMinHealth = 1;
        engine.DoNextAction(NULL); // rejuvenation on party
        engine.DoNextAction(NULL); // regrowth on party

        ai->partyMinHealth = 100;
        engine.DoNextAction(NULL); // follow

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">rejuvenation on party>regrowth on party>follow"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidNonCombatTestCase );
