#include "pch.h"

#include "EngineTestBase.h"
#include "../game/RogueActionFactory.h"
#include "../game/DpsRogueStrategy.h"

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
        
        assertActions(">reach melee>melee>mutilate>sinister strike>kidney shot>rupture>slice and dice>eviscerate");
    }

	void healHimself()
	{
		tickInMeleeRange();
		tickWithLowHealth(39);
		tickWithLowHealth(39);
		tickWithMyAttackerCount(3);

		assertActions(">melee>evasion>feint>vanish");
	}

	void interruptSpells()
	{
		tickInMeleeRange();

		tickWithTargetIsCastingNonMeleeSpell();

		assertActions(">melee>kick");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( DpsRogueTestCase );
