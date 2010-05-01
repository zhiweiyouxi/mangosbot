#include "pch.h"

#include "EngineTestBase.h"
#include "../game/GenericPaladinStrategy.h"

using namespace ai;


class TankPaladinTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( TankPaladinTestCase );
    CPPUNIT_TEST( combatVsMelee );
    CPPUNIT_TEST( paladinMustHoldAggro );
    CPPUNIT_TEST( healing );
    CPPUNIT_TEST( stopEnemyMove );
    CPPUNIT_TEST( buff );
	CPPUNIT_TEST( interruptSpells );
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new PaladinActionFactory(ai), "tank", NULL);

        addAura("devotion aura");
        addAura("seal of justice");
        addAura("blessing of kings");
        addAura("righteous fury");

		addAura("holy shield");

		ai->distanceToEnemy = 0;
    }
 
protected:
    void buff()
    {
        removeAura("righteous fury");
		tickInMeleeRange();
		addAura("righteous fury");
		
		removeAura("holy shield");
		tick();
		addAura("holy shield");

        assertActions(">righteous fury>holy shield");
    }

    void healing()
    {
		tickWithLowHealth(50);
        
		tickWithLowHealth(30);
		tickWithLowHealth(30);
		tickWithLowHealth(30);
		tickWithLowHealth(30);

        tick(); 

		tickWithLowHealth(20);

		spellAvailable("lay on hands");
		tickWithPartyLowHealth(20);

        assertActions(">flash of light>lifeblood>divine shield>holy light>gift of the naaru>divine protection>lay on hands>lay on hands on party");
    }
  
    void paladinMustHoldAggro()
    {
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);

		tickWithNoAggro();
		tickWithNoAggro();

        tick(); 

        assertActions(">holy wrath>consecration>avenger's shield>hand of reckoning>judgement of justice>exorcism");
    }

    void combatVsMelee()
    {
		tickOutOfMeleeRange();
        
        tick(); 
        tick(); 

		tickWithTargetLowHealth(24);

        assertActions(">reach melee>melee>judgement of light>hammer of wrath");
    }

    void stopEnemyMove()
    {
		tickWithTargetIsMoving();
		tickWithTargetIsMoving();
        
		tick(); 
		tick(); 

        assertActions(">hammer of justice>judgement of justice>melee>judgement of light");
    }

	void interruptSpells() 
	{
		tickWithTargetIsCastingNonMeleeSpell();

		tick();

		assertActions(">hammer of justice>melee");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankPaladinTestCase );
