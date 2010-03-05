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
    CPPUNIT_TEST( summonPet );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new HunterActionFactory(ai));
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
        engine->DoNextAction(NULL);     
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">aspect of the pack"));
    }
    void summonPet()
    {
        ai->hasPet = FALSE;
        engine->DoNextAction(NULL);
        
        ai->spellCooldowns.push_back("aspect of the hawk");
        ai->hasPet = TRUE;
        ai->petHealth = 0;
        engine->DoNextAction(NULL);
        
        ai->petHealth = 1;
        engine->DoNextAction(NULL);

        ai->spellCooldowns.remove("mend pet");
        ai->petAuras.push_back("mend pet");
        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">call pet>revive pet>mend pet>aspect of the pack"));
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( HunterNonCombatTestCase );
