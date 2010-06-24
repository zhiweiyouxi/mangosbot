#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/warrior/WarriorActionFactory.h"

using namespace ai;


class WarriorNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( WarriorNonCombatTestCase );
    //CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockAiManagerRegistry *ai;

public:
    void setUp()
    {
    }

protected:
    void buff()
    {
        ai = new MockAiManagerRegistry();

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
