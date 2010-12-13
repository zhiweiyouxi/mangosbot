#include "pch.h"

#include "aitest.h"
#include "EngineTestBase.h"
#include "EverythingUnavailableAiManagerRegistry.h"
#include <time.inl>
#include "../game/playerbot/strategy/druid/DruidActionFactory.h"
#include "../game/playerbot/strategy/paladin/PaladinActionFactory.h"
#include "../game/playerbot/strategy/warrior/WarriorActionFactory.h"
#include "../game/playerbot/strategy/warlock/WarlockActionFactory.h"
#include "../game/playerbot/strategy/mage/MageActionFactory.h"
#include "../game/playerbot/strategy/hunter/HunterActionFactory.h"
#include "../game/playerbot/strategy/priest/PriestActionFactory.h"
#include "../game/playerbot/strategy/shaman/ShamanActionFactory.h"

using namespace ai;


class PerformanceTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( PerformanceTestCase );
        CPPUNIT_TEST( druidBear );
        CPPUNIT_TEST( druidCat );
        CPPUNIT_TEST( paladin );
        CPPUNIT_TEST( warrior );
        CPPUNIT_TEST( warlock );
        CPPUNIT_TEST( priest );
        CPPUNIT_TEST( mage );
        CPPUNIT_TEST( hunter );
        CPPUNIT_TEST( shaman );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
        ai = new EverythingUnavailableAiManagerRegistry();
    }

protected:
    void run()
    {
        time_t timestamp = time(0);
        for (int i=0; i<100; i++) 
        {
            tick();
        }

        cout << "Time: " << (time(0) - timestamp);
    }

    void druidBear()
    {
        setupEngine(new DruidActionFactory(ai), "tank", NULL);
        engine->maxIterations = 100;
        run();
    }

    void paladin()
    {
        setupEngine(new PaladinActionFactory(ai), "tank", NULL);
        engine->maxIterations = 100;
        run();
    }

    void priest()
    {
        setupEngine(new PriestActionFactory(ai), "heal", NULL);
        engine->maxIterations = 100;
        run();
    }

    void mage()
    {
        setupEngine(new MageActionFactory(ai), "frost", NULL);
        engine->maxIterations = 100;
        run();
    }

    void hunter()
    {
        setupEngine(new HunterActionFactory(ai), "dps", NULL);
        engine->maxIterations = 100;
        run();
    }

    void warrior()
    {
        setupEngine(new WarriorActionFactory(ai), "tank", NULL);
        engine->maxIterations = 100;
        run();
    }

    void druidCat()
    {
        setupEngine(new DruidActionFactory(ai), "dps", NULL);
        engine->maxIterations = 100;
        run();
    }

    void warlock()
    {
        setupEngine(new WarlockActionFactory(ai), "tank", NULL);
        engine->maxIterations = 100;
        run();
    }

    void shaman()
    {
        setupEngine(new ShamanActionFactory(ai), "heal", NULL);
        engine->maxIterations = 100;
        run();
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( PerformanceTestCase );
