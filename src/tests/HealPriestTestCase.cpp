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
    CPPUNIT_TEST( dispel );
    CPPUNIT_TEST( fade );
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
    void healHimself()
    {
        ai->partyAuras.push_back("power word: fortitude");

        ai->health = 39;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // greater heal
        engine->DoNextAction(NULL); // renew
        engine->DoNextAction(NULL); // heal
        engine->DoNextAction(NULL); // lesser heal

        ai->health = 70;
        engine->DoNextAction(NULL); // shoot

        ai->health = 59;
        engine->DoNextAction(NULL); // flash heal
        ai->health = 70;

        ai->spellCooldowns.remove("shoot");
        engine->DoNextAction(NULL); // shoot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: shield>greater heal>renew>heal>lesser heal>shoot>flash heal>shoot"));
    }

    void nonCombat()
    {
        engine->removeStrategy("heal");
        engine->addStrategy("nc");
        engine->Init();

        ai->partyAuras.push_back("power word: fortitude");

        ai->health = 1;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // greater heal

        engine->DoNextAction(NULL); // renew

        engine->DoNextAction(NULL); // lesser heal

        ai->health = 90;

        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: shield>greater heal>renew>heal"));
    }

    void healOthers()
    {
        engine->DoNextAction(NULL); // shoot

        ai->partyMinHealth = 1;
        engine->DoNextAction(NULL); // power word: shield
        engine->DoNextAction(NULL); // greater heal
        engine->DoNextAction(NULL); // renew
        engine->DoNextAction(NULL); // heal
        engine->DoNextAction(NULL); // lesser heal

        ai->partyMinHealth = 70;
        ai->spellCooldowns.remove("shoot");
        engine->DoNextAction(NULL); // shoot

        ai->partyMinHealth = 59;
        engine->DoNextAction(NULL); // flash heal
        ai->partyMinHealth = 70;

        ai->spellCooldowns.remove("shoot");
        engine->DoNextAction(NULL); // shoot


        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">shoot>power word: shield on party>greater heal on party>renew on party>heal on party>lesser heal on party>shoot>flash heal on party>shoot"));
    }

    void buff()
    {
        ai->auras.remove("power word: fortitude");
        ai->auras.remove("divine spirit");
        ai->auras.remove("inner fire");
        ai->partyAuras.remove("power word: fortitude");
        ai->partyAuras.remove("divine spirit");

        engine->DoNextAction(NULL); // power word: fortitude
        ai->auras.push_back("power word: fortitude");

        ai->spellCooldowns.remove("power word: fortitude");
        engine->DoNextAction(NULL); // power word: fortitude on party

        engine->DoNextAction(NULL); // inner fire

        engine->DoNextAction(NULL); // divine spirit
        ai->auras.push_back("divine spirit");

        ai->spellCooldowns.remove("divine spirit");
        engine->DoNextAction(NULL); // divine spirit on party

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">power word: fortitude>divine spirit>inner fire>power word: fortitude on party>divine spirit on party"));
    }

    void fade()
    {
        engine->DoNextAction(NULL); 
        
        ai->myAttackerCount = 2;
        ai->attackerCount = 3;
        ai->partyMinHealth = 75;
        engine->DoNextAction(NULL); // fade
        engine->DoNextAction(NULL); // holy nova
        ai->myAttackerCount = 0;
        ai->attackerCount = 1;
        ai->partyMinHealth = 100;

        ai->spellCooldowns.remove("shoot");
        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">shoot>fade>holy nova>attack least threat"));
    }

    void dispel() 
    {
        engine->DoNextAction(NULL); // shoot

        ai->aurasToDispel = DISPEL_MAGIC;
        engine->DoNextAction(NULL); // dispel magic
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_MAGIC;
        ai->spellCooldowns.remove("dispel magic");
        engine->DoNextAction(NULL); // dispel magic on party
        ai->partyAurasToDispel = 0;


        ai->aurasToDispel = DISPEL_DISEASE;
        engine->DoNextAction(NULL); // abolish disease
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_DISEASE;
        ai->spellCooldowns.remove("abolish disease");
        engine->DoNextAction(NULL); // abolish disease on party
        ai->partyAurasToDispel = 0;


        ai->aurasToDispel = DISPEL_DISEASE;
        engine->DoNextAction(NULL); // cure disease
        ai->aurasToDispel = 0;

        ai->partyAurasToDispel = DISPEL_DISEASE;
        ai->spellCooldowns.remove("cure disease");
        engine->DoNextAction(NULL); // cure disease on party
        ai->partyAurasToDispel = 0;

        ai->targetAurasToDispel = DISPEL_MAGIC;
        ai->spellCooldowns.remove("dispel magic");
        engine->DoNextAction(NULL); // dispel magic on target
        ai->targetAurasToDispel = 0;

        ai->spellCooldowns.remove("shoot");
        engine->DoNextAction(NULL); // shoot

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">shoot>dispel magic>dispel magic on party>abolish disease>abolish disease on party>cure disease>cure disease on party>dispel magic on target>shoot"));
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( HealPriestTestCase );
