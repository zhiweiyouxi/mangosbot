#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericHunterStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class HunterNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( HunterNonCombatTestCase );
    CPPUNIT_TEST( buff );
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

        Engine engine(ai, new HunterActionFactory(ai));
        engine.addStrategy("hunter");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->auras.push_back("aspect of the hawk");
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">aspect of the hawk"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( HunterNonCombatTestCase );
