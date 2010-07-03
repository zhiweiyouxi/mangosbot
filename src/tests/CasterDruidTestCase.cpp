#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/druid/DruidActionFactory.h"

using namespace ai;


class CasterDruidTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( CasterDruidTestCase );
    CPPUNIT_TEST( combat);
    CPPUNIT_TEST( healHimself );
    CPPUNIT_TEST( healOthers );
	CPPUNIT_TEST( curePoison );
	CPPUNIT_TEST( resurrect );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "caster", NULL);

		addAura("moonkin form");
    }

protected:
    void combat()
    {
		removeAura("moonkin form");
		tick();
		addAura("moonkin form");

		tickInSpellRange();
		addTargetAura("faerie fire");

		tick();
		addTargetAura("insect swarm");

		tick();
		addTargetAura("moonfire");

        tick();
		tick();

		spellAvailable("starfire");
		tickInSpellRange();

		tickWithAttackerCount(3);
        
		assertActions(">S:moonkin form>T:faerie fire>T:insect swarm>T:moonfire>T:starfire>T:wrath>T:starfire>S:nature's grasp");
    }

	void healHimself()
    {
		tickInSpellRange();

		tickWithLowHealth(59);
		tickWithLowHealth(59);
                
		tick(); 
		addAura("moonkin form");

		tick();

		tickWithLowHealth(39);
		tickWithLowHealth(39);
        tickWithLowHealth(39);
        
        assertActions(">T:faerie fire>-moonkin form>S:regrowth>S:moonkin form>T:insect swarm>-moonkin form>S:rejuvenation>S:healing touch");
    }

	void healOthers()
    {
        tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(59);
        tickWithPartyLowHealth(39);
        tickWithPartyLowHealth(39);

        assertActions(">-moonkin form>P:regrowth>P:rejuvenation>P:healing touch");
    }

	void curePoison() 
	{
		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("abolish poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		tickWithAuraToDispel(DISPEL_POISON);

		spellAvailable("cure poison");
		tickWithPartyAuraToDispel(DISPEL_POISON);

		assertActions(">S:abolish poison>P:abolish poison>S:cure poison>P:cure poison");
	}

	void resurrect()
	{
		tickWithDeadPartyMember();
		tickWithDeadPartyMember();

		assertActions(">-moonkin form>P:rebirth");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( CasterDruidTestCase );
