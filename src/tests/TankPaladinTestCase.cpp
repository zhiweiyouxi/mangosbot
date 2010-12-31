#include "pch.h"

#include "aitest.h"
#include "../game/playerbot/strategy/paladin/PaladinActionFactory.h"

using namespace ai;


class TankPaladinTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( TankPaladinTestCase );
		CPPUNIT_TEST( combatVsMelee );
		CPPUNIT_TEST( paladinMustHoldAggro );
		CPPUNIT_TEST( healing );
		CPPUNIT_TEST( stopEnemyMove );
		CPPUNIT_TEST( buff );
		CPPUNIT_TEST( bmana );
		CPPUNIT_TEST( curePoison );
		CPPUNIT_TEST( cureMagic );
		CPPUNIT_TEST( cureDisease );
		CPPUNIT_TEST( interruptSpells );
		CPPUNIT_TEST( resistances );
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		EngineTestBase::setUp();
		setupEngine(new PaladinActionFactory(ai), "tank", NULL);
		engine->addStrategy("bhealth");
		engine->addStrategy("barmor");

        addAura("devotion aura");
        addAura("seal of justice");
        addAura("blessing of sanctuary");
        addAura("righteous fury");

		addAura("holy shield");

		moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0;
    }
 
protected:
    void bmana()
    {
		engine->removeStrategy("bhealth");
		engine->addStrategy("bmana");
	
        removeAura("seal of justice");
        tick();
        
		assertActions(">S:seal of wisdom");
	}

    void buff()
    {
        removeAura("devotion aura");
        removeAura("righteous fury");
        removeAura("blessing of sanctuary");
        removeAura("seal of justice");
        removeAura("holy shield");
        
        tick();
        addAura("devotion aura");
        
        tick();
        tick();
        addAura("seal of light");

        tick();
        tick(); 
        addAura("blessing of kings");
                
        tick();
        addAura("holy shield");

        tick();
        addAura("righteous fury");

        assertActions(">S:devotion aura>S:seal of light>S:seal of justice>S:blessing of sanctuary>S:blessing of kings>S:holy shield>S:righteous fury");
    }

    void healing()
    {
		tickWithLowHealth(50);
        
		tickWithLowHealth(30);
		tickWithLowHealth(30);

        tick(); 

		tickWithLowHealth(19);

		spellAvailable("lay on hands");
		tickWithPartyLowHealth(20);

		assertActions(">S:flash of light>S:divine shield>S:holy light>S:divine protection>S:lay on hands>P:lay on hands");
    }
  
    void paladinMustHoldAggro()
    {
		tickWithAttackerCount(2);
		tickWithAttackerCount(2);

		tickWithAttackerCount(3);
		tickWithAttackerCount(3);

		tickWithNoAggro();
		tickWithNoAggro();

		assertActions(">T:hammer of the righteous>T:avenger's shield>T:consecration>T:holy wrath>T:hand of reckoning>T:judgement of justice");
    }

    void combatVsMelee()
    {
		tickOutOfMeleeRange();
        
        tick(); 
        tick(); 

		tickWithTargetLowHealth(24);

        assertActions(">reach melee>melee>T:judgement of light>T:hammer of wrath");
    }

    void stopEnemyMove()
    {
		tickWithTargetIsMoving();
        
		tick(); 
		tick(); 

        assertActions(">T:hammer of justice>melee>T:judgement of light");
    }

	void interruptSpells() 
	{
		tickWithTargetIsCastingNonMeleeSpell();

		tick();

		assertActions(">T:hammer of justice>melee");
	}

    void cureDisease()
    {
        cureKind(DISPEL_DISEASE);
		assertActions(">S:cleanse>P:cleanse>S:purify>P:purify");
    }

	void curePoison()
	{
		cureKind(DISPEL_POISON);
		assertActions(">S:cleanse>P:cleanse>S:purify>P:purify");
	}

	void cureMagic()
	{
		spellAvailable("cleanse");
		tickWithAuraToDispel(DISPEL_MAGIC);

		spellAvailable("cleanse");
		tickWithPartyAuraToDispel(DISPEL_MAGIC);
		
		assertActions(">S:cleanse>P:cleanse");
	}

    void cureKind(DispelType type) 
    {
        spellAvailable("cleanse");
        tickWithAuraToDispel(type);

        spellAvailable("cleanse");
        tickWithPartyAuraToDispel(type);

        spellAvailable("purify");
        tickWithAuraToDispel(type);

        spellAvailable("purify");
        tickWithPartyAuraToDispel(type);
    }

	void resistances()
	{
		engine->addStrategy("rshadow");
		tick();
	
		engine->addStrategy("rfrost");
		tick();
	
		engine->addStrategy("rfire");
		tick();

		assertActions(">S:shadow resistance aura>S:frost resistance aura>S:fire resistance aura");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TankPaladinTestCase );
