#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/HealPriestStrategy.h"
#include "../game/PriestActionFactory.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class HealPriestTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( HealPriestTestCase );
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
    CPPUNIT_TEST( buff );
    CPPUNIT_TEST( nonCombat );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new PriestActionFactory(ai));
        engine->addStrategy("heal");
        engine->Init();

        ai->auras.push_back("power word: fortitude");
        ai->auras.push_back("divine spirit");
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
    void healHimself()
    {
        ai->partyAuras.push_back("power word: fortitude");

        ai->health = 1;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // heal

        engine->DoNextAction(NULL); // renew
        
        engine->DoNextAction(NULL); // lesser heal

        ai->health = 70;

        engine->DoNextAction(NULL); // shoot
        
        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: shield>heal>renew>lesser heal>shoot"));
    }

    void nonCombat()
    {
        engine->removeStrategy("heal");
        engine->addStrategy("nc");
        engine->Init();

        ai->partyAuras.push_back("power word: fortitude");

        ai->health = 1;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // heal

        engine->DoNextAction(NULL); // renew

        engine->DoNextAction(NULL); // lesser heal

        ai->health = 70;

        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: shield>heal>renew>lesser heal"));
    }

    void healOthers()
    {
        engine->DoNextAction(NULL); // shoot

        ai->partyMinHealth = 1;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // heal

        engine->DoNextAction(NULL); // renew
        engine->DoNextAction(NULL); // lesser heal

        ai->partyMinHealth = 70;

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">shoot>power word: shield on party>heal on party>renew on party>lesser heal on party"));
    }

    void buff()
    {
        ai->auras.remove("power word: fortitude");
        ai->auras.remove("divine spirit");
        ai->partyAuras.remove("power word: fortitude");
        ai->partyAuras.remove("divine spirit");

        engine->DoNextAction(NULL); // power word: fortitude
        ai->auras.push_back("power word: fortitude");

        ai->spellCooldowns.remove("power word: fortitude");
        engine->DoNextAction(NULL); // power word: fortitude on party

        engine->DoNextAction(NULL); // divine spirit
        ai->auras.push_back("divine spirit");

        ai->spellCooldowns.remove("divine spirit");
        engine->DoNextAction(NULL); // divine spirit on party

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: fortitude>power word: fortitude on party>divine spirit>divine spirit on party"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( HealPriestTestCase );
