#include "pch.h"

#include "../aitest.h"
#include "../../game/playerbot/strategy/Warlock/WarlockAiObjectContext.h"
#include "EfficiencyActionExecutionListener.h"

using namespace ai;


class WarlockEfficiencyTestCase : public EngineTestBase
{
  CPPUNIT_TEST_SUITE( WarlockEfficiencyTestCase );
  CPPUNIT_TEST( lvl19_dps );
  CPPUNIT_TEST( lvl19_tank );
  CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
    }

protected:
    map<string, SpellInfo> lvl19()
    {
        map<string, SpellInfo> spellInfo;
        spellInfo["corruption"] = SpellInfo(42, 0, 15, 90);
        spellInfo["immolate"] = SpellInfo(60, 0, 15, 19 + 40);
        spellInfo["shadow bolt"] = SpellInfo(58, 2.8, 0, 52);
        spellInfo["curse of agony"] = SpellInfo(35, 0, 24, 180);
        spellInfo["shoot"] = SpellInfo(0, 0, 1, 15);
        return spellInfo;
    }

    void refresh(map<string, SpellInfo> spellInfo)
    {
        for (map<string, SpellInfo>::iterator i = spellInfo.begin(); i != spellInfo.end(); ++i)
        {
            spellAvailable(i->first);
        }
    }

 	void lvl19_dps()
	{
 	    map<string, SpellInfo> spellInfo = lvl19();
        setupEngine(new WarlockAiObjectContext(ai), "dps", "aoe", NULL);
        EfficiencyActionExecutionListener* listener = new EfficiencyActionExecutionListener(ai, spellInfo, 888);
        engine->AddActionExecutionListener(listener);

        while (listener->CanContinue())
 	    {
            tick();
            refresh(spellInfo);
 	    }
        cout << "Act: " << ai->buffer << "\n";
        listener->Report();
	}

 	void lvl19_tank()
	{
 	    map<string, SpellInfo> spellInfo = lvl19();
        setupEngine(new WarlockAiObjectContext(ai), "tank", "aoe", NULL);
        EfficiencyActionExecutionListener* listener = new EfficiencyActionExecutionListener(ai, spellInfo, 888);
        engine->AddActionExecutionListener(listener);

        while (listener->CanContinue())
 	    {
            tick();
            refresh(spellInfo);
 	    }
        cout << "Act: " << ai->buffer << "\n";
        listener->Report();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( WarlockEfficiencyTestCase );
