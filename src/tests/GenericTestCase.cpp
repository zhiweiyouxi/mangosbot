#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/DruidActionFactory.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;

class GenericTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( GenericTestCase );
    CPPUNIT_TEST( timeToPanic );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
    void setUp()
    {
    }

protected:
    void timeToPanic()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("bear tank");
        engine.Init();

        ai->health = 1;
        ai->mana = 1;
        engine.DoNextAction(NULL); // nothing is available - only flee

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">flee"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( GenericTestCase );
