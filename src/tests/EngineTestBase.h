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
    virtual void setUp();
    virtual void tearDown();

private:
	void va_generic(void (EngineTestBase::*callback)(const char*), va_list vl);

protected:
	virtual void setupEngine(ActionFactory* actionFactory, ...);
	void setupEngineCallback(const char* name);
	void tick();
	void assertActions(const char* expected);

	void tickWithNoTarget();
	void spellUnavailable(const char* spell);
	void tickWithSpellUnavailable(const char* spell);
	void tickWithSpellAvailable(const char* spell);
	void spellAvailable(const char* spell);
	void addAura(const char* spell);
	void addTargetAura(const char* spell);
	void removeTargetAura(const char* spell);
	void addPartyAura(const char* spell);
	void removePartyAura(const char* spell);
	void removeAura(const char* spell);
	void tickOutOfSpellRange();
	void tickOutOfMeleeRange();
	void tickInMeleeRange();
	void tickInSpellRange();
	void tickWithNoAggro();
	void tickWithRage(int amount);
	void tickWithAttackerCount(int count);
	void tickWithMyAttackerCount(int count);
	void tickWithLowHealth(int amount);
	void tickWithPartyLowHealth(int amount);
	void tickWithAuraToDispel(uint32 type);
	void tickWithPartyAuraToDispel(uint32 type);
	void lowHealth(int amount);
	void lowMana(int amount);
	void healthRestored();
	void tickWithComboPoints(int amount);
	void tickWithTargetIsCastingNonMeleeSpell();
	void tickWithBalancePercent(int percent);
	void tickWithNoPet();
	void tickWithPetLowHealth(int amount);
	void tickWithLowMana(int amount);
	void tickWithTargetLowHealth(int amount);
	void tickWithTargetIsMoving();
	void tickWithLootAvailable();
	void tickWithNoFood();
	void tickWithNoDrink();
	void itemAvailable(const char* item, int amount);
	void tickWithDeadPartyMember();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;
};
