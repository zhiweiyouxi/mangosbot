#include "pch.h"
#include "aitest.h"
#include "EngineTestBase.h"
#include "MockedTargets.h"

void EngineTestBase::setUp()
{
	ai = new MockAiManagerRegistry();
	spellManager = (MockAiSpellManager*)ai->GetSpellManager();
	targetManager = (MockAiTargetManager*)ai->GetTargetManager();
	statsManager = (MockAiStatsManager*)ai->GetStatsManager();
	moveManager = (MockAiMoveManager*)ai->GetMoveManager();
	inventoryManager = (MockAiInventoryManager*)ai->GetInventoryManager();
	socialManager = (MockAiSocialManager*)ai->GetSocialManager();
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
    targetManager->haveTarget = FALSE;
    statsManager->myAttackerCount = 0;
    
	tick();
    
	statsManager->myAttackerCount = 1;
    targetManager->haveTarget = TRUE;
}

void EngineTestBase::spellUnavailable(const char* spell)
{
	spellManager->spellCooldowns.push_back(spell);
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
	spellManager->spellCooldowns.remove(spell);
}

void EngineTestBase::addAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetSelf()].push_back(spell);
}

void EngineTestBase::removeAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetSelf()].remove(spell);
}

void EngineTestBase::tickOutOfSpellRange()
{
	moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 49.0f;
    tick(); 
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;	
}

void EngineTestBase::tickOutOfMeleeRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;
    tick(); 
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f;	
}

void EngineTestBase::tickInMeleeRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 0.0f;
	tick();
}

void EngineTestBase::tickWithNoAggro()
{
    statsManager->aggro = FALSE;
    tick();
    statsManager->aggro = TRUE;
}

void EngineTestBase::tickWithRage(int amount)
{
	statsManager->rage[MockedTargets::GetSelf()] = amount;
    tick();
    statsManager->rage[MockedTargets::GetSelf()] = 0;
}

void EngineTestBase::tickWithEnergy(int amount)
{
	statsManager->energy[MockedTargets::GetSelf()] = amount;
	tick();
	statsManager->energy[MockedTargets::GetSelf()] = 0;
}

void EngineTestBase::tickWithAttackerCount(int count)
{
	statsManager->attackerCount = count;
	tick();
	statsManager->attackerCount = 1;
}

void EngineTestBase::tickWithMyAttackerCount(int count)
{
	statsManager->myAttackerCount = count;
	tickWithAttackerCount(count + 1);
	statsManager->myAttackerCount = 1;
}

void EngineTestBase::tickWithLowHealth(int amount)
{
	lowHealth(amount);
	tick();
	healthRestored();
}

void EngineTestBase::tickWithPartyLowHealth(int amount)
{
	statsManager->health[MockedTargets::GetPartyMember()] = amount;
	tick();
	statsManager->health[MockedTargets::GetPartyMember()] = 100;
}

void EngineTestBase::tickWithAuraToDispel(uint32 type)
{
	spellManager->dispels[MockedTargets::GetSelf()] = type;
	tick();
	spellManager->dispels[MockedTargets::GetSelf()] = 0;
}

void EngineTestBase::tickWithPartyAuraToDispel(uint32 type)
{
	spellManager->dispels[MockedTargets::GetPartyMember()] = type;
	tick();
	spellManager->dispels[MockedTargets::GetPartyMember()] = 0;
}

void EngineTestBase::lowHealth(int amount)
{
	statsManager->health[MockedTargets::GetSelf()] = amount;
}

void EngineTestBase::lowMana(int amount)
{
	statsManager->mana[MockedTargets::GetSelf()] = amount;
}

void EngineTestBase::healthRestored()
{
	statsManager->health[MockedTargets::GetSelf()] = 100;
}

void EngineTestBase::tickWithComboPoints(int amount)
{
	statsManager->comboPoints[MockedTargets::GetSelf()] = amount;
	tick();
	statsManager->comboPoints[MockedTargets::GetSelf()] = 0;
}

void EngineTestBase::tickWithTargetIsCastingNonMeleeSpell() 
{
    spellManager->targetIsCastingNonMeleeSpell = true;
    tick();
    spellManager->targetIsCastingNonMeleeSpell = false;
}

void EngineTestBase::tickWithBalancePercent(int percent)
{
	statsManager->balancePercent = percent;
	tick();
	statsManager->balancePercent = 100;
}

void EngineTestBase::tickWithNoPet()
{
	targetManager->hasPet = false;
	tick();
	targetManager->hasPet = true;
}

void EngineTestBase::tickWithPetLowHealth(int amount)
{
	statsManager->health[MockedTargets::GetPet()] = amount;
	tick();
	statsManager->health[MockedTargets::GetPet()] = 100;
}

void EngineTestBase::tickWithLowMana(int amount)
{
    statsManager->mana[MockedTargets::GetSelf()] = amount;
    tick();
    statsManager->mana[MockedTargets::GetSelf()] = 100;
}

void EngineTestBase::tickWithTargetLowHealth(int amount)
{
	statsManager->health[MockedTargets::GetCurrentTarget()] = amount;
    tick();
    statsManager->health[MockedTargets::GetCurrentTarget()] = 100;
}
void EngineTestBase::tickWithTargetIsMoving()
{
    moveManager->moving[MockedTargets::GetCurrentTarget()] = true;
    tick();
    moveManager->moving[MockedTargets::GetCurrentTarget()] = false;
}

void EngineTestBase::tickInSpellRange()
{
    moveManager->distanceTo[MockedTargets::GetCurrentTarget()] = 15.0f;
    tick();
}

void EngineTestBase::addTargetAura(const char* spell)
{
	spellManager->auras[MockedTargets::GetCurrentTarget()].push_back(spell);
}

void EngineTestBase::removeTargetAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetCurrentTarget()].remove(spell);
}

void EngineTestBase::addPartyAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetPartyMember()].push_back(spell);
}

void EngineTestBase::removePartyAura(const char* spell)
{
    spellManager->auras[MockedTargets::GetPartyMember()].remove(spell);
}

void EngineTestBase::tickWithLootAvailable()
{
	inventoryManager->lootAvailable = true;
	tick();
	inventoryManager->lootAvailable = false;
}

void EngineTestBase::tickWithNoDrink()
{
	inventoryManager->hasDrink = false;
	tick();
	inventoryManager->hasDrink = true;
}

void EngineTestBase::tickWithNoFood()
{
	inventoryManager->hasFood = false;
	tick();
	inventoryManager->hasFood = true;
}

void EngineTestBase::itemAvailable(const char* item, int amount)
{
	inventoryManager->itemCounts[std::string(item)] = amount;
}

void EngineTestBase::tickWithDeadPartyMember() 
{
	targetManager->deadPartyMember = true;
	tick();
	targetManager->deadPartyMember = false;
}

void EngineTestBase::tickBehindTarget()
{
    moveManager->isBehind[MockedTargets::GetCurrentTarget()] = true;
    tick();
    moveManager->isBehind[MockedTargets::GetCurrentTarget()] = false;
}