#include "pch.h"
#include "EngineTestBase.h"

void EngineTestBase::setUp()
{
	ai = new MockPlayerbotAIFacade();
}

void EngineTestBase::tearDown()
{
    if (engine)
        delete engine;
    if (ai) 
        delete ai;
}

void EngineTestBase::va_generic(void (EngineTestBase::*callback)(const char*), va_list vl)
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


void EngineTestBase::setupEngine(ActionFactory* actionFactory, ...)
{
    engine = new Engine(ai, actionFactory);
    
	va_list vl;
	va_start(vl, actionFactory);

	va_generic(&EngineTestBase::setupEngineCallback, vl);
    
	engine->testMode = true;
	engine->Init();
}

void EngineTestBase::setupEngineCallback(const char* name)
{
	engine->addStrategy(name);
}

void EngineTestBase::tick() 
{
	engine->DoNextAction(NULL);
}

void EngineTestBase::assertActions(const char* expected) 
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

void EngineTestBase::tickWithNoTarget()
{
    ai->haveTarget = FALSE;
    ai->myAttackerCount = 0;
    
	tick();
    
	ai->myAttackerCount = 1;
    ai->haveTarget = TRUE;
}

void EngineTestBase::spellUnavailable(const char* spell)
{
	ai->spellCooldowns.push_back(spell);
}

void EngineTestBase::tickWithSpellUnavailable(const char* spell)
{
	spellUnavailable(spell);
	tick();
}

void EngineTestBase::tickWithSpellAvailable(const char* spell) 
{
	spellAvailable(spell);
	tick();
}

void EngineTestBase::spellAvailable(const char* spell)
{
	ai->spellCooldowns.remove(spell);
}

void EngineTestBase::addAura(const char* spell)
{
	ai->auras.push_back(spell);
}

void EngineTestBase::removeAura(const char* spell)
{
	ai->auras.remove(spell);
}

void EngineTestBase::tickOutOfSpellRange()
{
    ai->distanceToEnemy = 49.0f;
    tick(); 
    ai->distanceToEnemy = 15.0f;	
}

void EngineTestBase::tickOutOfMeleeRange()
{
    ai->distanceToEnemy = 15.0f;
    tick(); 
    ai->distanceToEnemy = 0.0f;	
}

void EngineTestBase::tickInMeleeRange()
{
    ai->distanceToEnemy = 0.0f;
	tick();
}

void EngineTestBase::tickWithNoAggro()
{
    ai->aggro = FALSE;
    tick();
    ai->aggro = TRUE;
}

void EngineTestBase::tickWithRage(int amount)
{
    ai->rage = amount;
    tick();
    ai->rage = 0;
}

void EngineTestBase::tickWithEnergy(int amount)
{
	ai->energy = amount;
	tick();
	ai->energy = 0;
}

void EngineTestBase::tickWithAttackerCount(int count)
{
	ai->attackerCount = count;
	tick();
	ai->attackerCount = 1;
}

void EngineTestBase::tickWithMyAttackerCount(int count)
{
	ai->myAttackerCount = count;
	tickWithAttackerCount(count + 1);
	ai->myAttackerCount = 1;
}

void EngineTestBase::tickWithLowHealth(int amount)
{
	lowHealth(amount);
	tick();
	healthRestored();
}

void EngineTestBase::tickWithPartyLowHealth(int amount)
{
	ai->partyMinHealth = amount;
	tick();
	ai->partyMinHealth = 100;
}

void EngineTestBase::tickWithAuraToDispel(uint32 type)
{
	ai->aurasToDispel = type;
	tick();
	ai->aurasToDispel = 0;
}

void EngineTestBase::tickWithPartyAuraToDispel(uint32 type)
{
	ai->partyAurasToDispel = type;
	tick();
	ai->partyAurasToDispel = 0;
}

void EngineTestBase::lowHealth(int amount)
{
	ai->health = amount;
}

void EngineTestBase::lowMana(int amount)
{
	ai->mana = amount;
}

void EngineTestBase::healthRestored()
{
	ai->health = 100;
}

void EngineTestBase::tickWithComboPoints(int amount)
{
	ai->comboPoints = amount;
	tick();
	ai->comboPoints = 0;
}

void EngineTestBase::tickWithTargetIsCastingNonMeleeSpell() 
{
    ai->targetIsCastingNonMeleeSpell = true;
    tick();
    ai->targetIsCastingNonMeleeSpell = false;
}

void EngineTestBase::tickWithBalancePercent(int percent)
{
	ai->balancePercent = percent;
	tick();
	ai->balancePercent = 100;
}

void EngineTestBase::tickWithNoPet()
{
	ai->hasPet = FALSE;
	tick();
	ai->hasPet = TRUE;
}

void EngineTestBase::tickWithPetLowHealth(int amount)
{
	ai->petHealth = amount;
	tick();
	ai->petHealth = 100;
}

void EngineTestBase::tickWithLowMana(int amount)
{
    ai->mana = amount;
    tick();
    ai->mana = 100;
}

void EngineTestBase::tickWithTargetLowHealth(int amount)
{
    ai->targetHealth = amount;
    tick();
    ai->targetHealth = 100;
}
void EngineTestBase::tickWithTargetIsMoving()
{
    ai->targetIsMoving = true;
    tick();
    ai->targetIsMoving = false;
}

void EngineTestBase::tickInSpellRange()
{
    ai->distanceToEnemy = 15.0f;
    tick();
}

void EngineTestBase::addTargetAura(const char* spell)
{
    ai->targetAuras.push_back(spell);
}

void EngineTestBase::removeTargetAura(const char* spell)
{
    ai->targetAuras.remove(spell);
}

void EngineTestBase::addPartyAura(const char* spell)
{
    ai->partyAuras.push_back(spell);
}

void EngineTestBase::removePartyAura(const char* spell)
{
    ai->partyAuras.remove(spell);
}

void EngineTestBase::tickWithLootAvailable()
{
	ai->lootAvailable = true;
	tick();
	ai->lootAvailable = false;
}

void EngineTestBase::tickWithNoDrink()
{
	ai->hasDrink = false;
	tick();
	ai->hasDrink = true;
}

void EngineTestBase::tickWithNoFood()
{
	ai->hasFood = false;
	tick();
	ai->hasFood = true;
}

void EngineTestBase::itemAvailable(const char* item, int amount)
{
	ai->itemCounts[std::string(item)] = amount;
}

void EngineTestBase::tickWithDeadPartyMember() 
{
	ai->deadPartyMember = true;
	tick();
	ai->deadPartyMember = false;
}
