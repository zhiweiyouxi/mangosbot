#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/GenericPaladinStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class PaladinNonCombatTestCase : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PaladinNonCombatTestCase );
        CPPUNIT_TEST( buff );
    CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new PaladinActionFactory(ai));
        engine->addStrategy("nc");
        engine->Init();

        ai->attackerCount = 0;
    }

protected:
    void buff()
    {
        engine->DoNextAction(NULL);
        ai->auras.push_back("devotion aura");

		ai->spellCooldowns.push_back("seal of justice");
		ai->spellCooldowns.push_back("seal of light");
		engine->DoNextAction(NULL); 
		ai->spellCooldowns.remove("seal of justice");
        engine->DoNextAction(NULL); 
		ai->spellCooldowns.remove("seal of light");
		engine->DoNextAction(NULL); 
		ai->auras.push_back("seal of light");

        engine->DoNextAction(NULL); 
        ai->auras.push_back("blessing of kings");
        ai->spellCooldowns.remove("blessing of kings");

        engine->DoNextAction(NULL); 
        ai->partyAuras.push_back("blessing of kings");

        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(ai->buffer == ">devotion aura>seal of righteousness>seal of justice>seal of light>blessing of kings>blessing of kings on party");
    }


};

CPPUNIT_TEST_SUITE_REGISTRATION( PaladinNonCombatTestCase );
