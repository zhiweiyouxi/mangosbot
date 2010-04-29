#pragma once;

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;

class EngineTestBase : public CPPUNIT_NS::TestFixture
{
public:
    virtual void setUp()
    {
		ai = new MockPlayerbotAIFacade();
	}

    virtual void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

private:
	void va_generic(void (EngineTestBase::*callback)(const char*), va_list vl)
	{
		const char* cur = NULL;
		do 
		{
			cur = va_arg(vl, const char*);
			if (cur)
				(this->*callback)(cur);
		}
		while (cur);

		va_end(vl);
	}

protected:
	virtual void setupEngine(ActionFactory* actionFactory, ...)
	{
        engine = new Engine(ai, actionFactory);
        
		va_list vl;
		va_start(vl, actionFactory);

		va_generic(&EngineTestBase::setupEngineCallback, vl);
        
		engine->Init();
    }

	void setupEngineCallback(const char* name)
	{
		engine->addStrategy(name);
	}

	void tick() 
	{
		engine->DoNextAction(NULL);
	}

	void assertActions(const char* expected) 
	{
		bool pass = ai->buffer == expected;
		if (!pass)
		{
			std::cout << "\n===\n";
			std::cout << "Exp: " << expected << "\n";
			std::cout << "Act: " << ai->buffer << "\n";
			std::cout << "===\n";
		}
        CPPUNIT_ASSERT(pass);
	}

	void similateNoTarget()
	{
        ai->haveTarget = FALSE;
        ai->myAttackerCount = 0;
        
		tick();
        
		ai->myAttackerCount = 1;
        ai->haveTarget = TRUE;
	}

	void spellUnavailable(const char* spell)
	{
		ai->spellCooldowns.push_back(spell);
	}

	void tickWithSpellUnavailable(const char* spell)
	{
		spellUnavailable(spell);
		tick();
	}

	void tickWithSpellAvailable(const char* spell) 
	{
		spellAvailable(spell);
		tick();
	}

	void spellAvailable(const char* spell)
	{
		ai->spellCooldowns.remove(spell);
	}

	void addAura(const char* spell)
	{
		ai->auras.push_back(spell);
	}

	void removeAura(const char* spell)
	{
		ai->auras.remove(spell);
	}

	void tickOutOfSpellRange()
	{
        ai->distanceToEnemy = 49.0f;
        tick(); 
        ai->distanceToEnemy = 15.0f;	
	}

	void tickOutOfMeleeRange()
	{
        ai->distanceToEnemy = 15.0f;
        tick(); 
        ai->distanceToEnemy = 0.0f;	
	}

	void tickInMeleeRange()
	{
        ai->distanceToEnemy = 0.0f;
		tick();
	}

	void tickWithNoAggro()
	{
        ai->aggro = FALSE;
        tick();
        ai->aggro = TRUE;
	}

	void tickWithRage(int amount)
	{
        ai->rage = amount;
        tick();
        ai->rage = 0;
	}

	void tickWithAttackerCount(int count)
	{
		ai->attackerCount = count;
		tick();
		ai->attackerCount = 1;
	}

	void tickWithMyAttackerCount(int count)
	{
		ai->myAttackerCount = count;
		tickWithAttackerCount(count + 1);
		ai->myAttackerCount = 1;
	}

	void tickWithLowHealth(int amount)
	{
		lowHealth(amount);
		tick();
		healthRestored();
	}

	void tickWithPartyLowHealth(int amount)
	{
		ai->partyMinHealth = amount;
		tick();
		ai->partyMinHealth = 100;
	}

	void tickWithAuraToDispel(uint32 type)
	{
		ai->aurasToDispel = type;
		tick();
		ai->aurasToDispel = 0;
	}

	void tickWithPartyAuraToDispel(uint32 type)
	{
		ai->partyAurasToDispel = type;
		tick();
		ai->partyAurasToDispel = 0;
	}

	void lowHealth(int amount)
	{
		ai->health = amount;
	}

	void healthRestored()
	{
		ai->health = 100;
	}

	void tickWithComboPoints(int amount)
	{
		ai->comboPoints = amount;
		tick();
		ai->comboPoints = 0;
	}
	
	void tickWithTargetIsCastingNonMeleeSpell() 
	{
        ai->targetIsCastingNonMeleeSpell = true;
        tick();
        ai->targetIsCastingNonMeleeSpell = false;
	}

	void tickWithBalancePercent(int percent)
	{
		ai->balancePercent = percent;
		tick();
		ai->balancePercent = 100;
	}

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;
};
