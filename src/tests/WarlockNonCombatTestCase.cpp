#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/WarlockActionFactory.h"
#include "../game/GenericWarlockNonCombatStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class WarlockNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( WarlockNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new WarlockActionFactory(ai));
        engine->addStrategy("nc");
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
    void buff()
    {
        engine->DoNextAction(NULL);
        ai->auras.push_back("demon armor");
        ai->spellCooldowns.remove("demon armor");

        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">demon armor"));
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarlockNonCombatTestCase );
