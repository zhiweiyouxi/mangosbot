#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/DpsPriestStrategy.h"
#include "../game/PriestActionFactory.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class DpsPriestTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DpsPriestTestCase );
    CPPUNIT_TEST( combat );
    CPPUNIT_TEST( pickNewTarget );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new PriestActionFactory(ai));
        engine->addStrategy("dps");
        engine->Init();

        ai->auras.push_back("power word: fortitude");
        ai->auras.push_back("divine spirit");
        ai->auras.push_back("inner fire");
        ai->partyAuras.push_back("power word: fortitude");
        ai->partyAuras.push_back("divine spirit");
    }

    void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

protected:
    void pickNewTarget()
    {
        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // attack least threat
        ai->myAttackerCount = 1;
        ai->resetSpells();
        engine->DoNextAction(NULL); // concussive shot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">attack least threat>mind flay"));

    }

    void combat()
    {
        engine->DoNextAction(NULL); // shadow word: pain
        engine->DoNextAction(NULL); // devouring plague
        engine->DoNextAction(NULL); // mind blast
        engine->DoNextAction(NULL); // holy nova
        ai->myAttackerCount = 0;
        engine->DoNextAction(NULL); // mind flay
        ai->myAttackerCount = 1;
        engine->DoNextAction(NULL); // smite
        engine->DoNextAction(NULL); // shoot

        // heal if need
        ai->health = 1;
        engine->DoNextAction(NULL); // shirld
        engine->DoNextAction(NULL); // greater heal
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">devouring plague>shadow word: pain>mind blast>holy fire>attack least threat>mind flay>shoot>power word: shield>greater heal"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsPriestTestCase );
