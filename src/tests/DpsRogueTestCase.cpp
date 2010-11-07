#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/rogue/RogueActionFactory.h"

using namespace ai;


class DpsRogueTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( DpsRogueTestCase );
		CPPUNIT_TEST( combatVsMelee );
		CPPUNIT_TEST( healHimself );
		CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new RogueActionFactory(ai), "dps", NULL);
    }

protected:
    void combatVsMelee()
    {
		tickOutOfMeleeRange();
		tickInMeleeRange();

		tickWithEnergy(70);
        tickWithEnergy(70);

        tickWithComboPoints(5);
        tickWithComboPoints(5);
		tickWithComboPoints(5);
		tickWithComboPoints(5);

        tickBehindTarget();
        
        assertActions(">reach melee>melee>T:mutilate>T:sinister strike>T:kidney shot>T:rupture>T:slice and dice>T:eviscerate>T:backstab");
    }

	void healHimself()
	{
		tickInMeleeRange();
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithMyAttackerCount(3);

		assertActions(">melee>S:evasion>S:feint>S:vanish");
	}

	void interruptSpells()
	{
		tickInMeleeRange();

		tickWithTargetIsCastingNonMeleeSpell();

		assertActions(">melee>T:kick");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsRogueTestCase );
