#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/MageActionFactory.h"
#include "../game/GenericMageNonCombatStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class MageNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MageNonCombatTestCase );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new MageActionFactory(ai));
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
        ai->auras.push_back("arcane intellect");
        ai->spellCooldowns.remove("arcane intellect");

        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">arcane intellect>arcane intellect on party"));
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( MageNonCombatTestCase );
