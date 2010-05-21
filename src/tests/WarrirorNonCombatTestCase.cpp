#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericWarriorStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class WarriorNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( WarriorNonCombatTestCase );
    //CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;

public:
    void setUp()
    {
    }

protected:
    void buff()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new WarriorActionFactory(ai));
        engine.addStrategy("nc");
        engine.Init();

        engine.DoNextAction(NULL);
        engine.DoNextAction(NULL);

        std::cout << ai->buffer;
		CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">S:defensive stance"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarriorNonCombatTestCase );
