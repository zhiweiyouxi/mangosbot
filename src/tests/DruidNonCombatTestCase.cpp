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
    CPPUNIT_TEST( buff );
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

        ai->attackerCount = 0;
        ai->partyMinHealth = 1;
        ai->auras.push_back("dire bear form");
        engine.DoNextAction(NULL); // caster form
        engine.DoNextAction(NULL); // regrowth on party

        ai->partyMinHealth = 100;
        engine.DoNextAction(NULL); // follow

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">-dire bear form>regrowth on party>follow"));
    }

    void buff()
    {
        ai = new MockPlayerbotAIFacade();

        Engine engine(ai, new DruidActionFactory(ai));
        engine.addStrategy("druid non combat");
        engine.Init();

        engine.DoNextAction(NULL);
        ai->auras.push_back("mark of the wild");
        
        engine.DoNextAction(NULL);
        ai->auras.push_back("thorns");
        ai->spellCooldowns.remove("mark of the wild");
        
        engine.DoNextAction(NULL);
        engine.DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">thorns>mark of the wild>mark of the wild on party"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( DruidNonCombatTestCase );
