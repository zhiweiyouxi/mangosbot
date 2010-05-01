#include "pch.h"

#include "../game/Action.h"
#include "../game/ActionBasket.h"
#include "../game/Queue.h"
#include "../game/Trigger.h"
#include "../game/Engine.h"
#include "../game/WarlockActionFactory.h"
#include "../game/GenericWarlockStrategy.h"

#include "MockPlayerbotAIFacade.h"

using namespace ai;


class FrostWarlockTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( FrostWarlockTestCase );
      CPPUNIT_TEST( combatVsMelee );
      CPPUNIT_TEST( summonPet );
  CPPUNIT_TEST_SUITE_END();

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;

public:
    void setUp()
    {
        ai = new MockPlayerbotAIFacade();

        engine = new Engine(ai, new WarlockActionFactory(ai));
        engine->addStrategy("dps");
        engine->Init();
    }

    void tearDown()
    {
        if (engine)
            delete engine;
        if (ai) 
            delete ai;
    }

protected:
 	void combatVsMelee()
	{
        engine->DoNextAction(NULL); 
        ai->targetAuras.push_back("immolate");
        engine->DoNextAction(NULL); 
        ai->targetAuras.push_back("corruption");
        engine->DoNextAction(NULL); 
        ai->targetAuras.push_back("curse of agony");
        
        ai->health = 49;
        engine->DoNextAction(NULL); 
        ai->health = 70;
        ai->targetIsCastingNonMeleeSpell = true;
        engine->DoNextAction(NULL); 
        ai->targetIsCastingNonMeleeSpell = false;

        engine->DoNextAction(NULL); 
        engine->DoNextAction(NULL); 

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">immolate>corruption>curse of agony>drain life>drain mana>shadow bolt>shoot"));
	}

    void summonPet()
    {
        ai->hasPet = FALSE;
        ai->spellCooldowns.push_back("summon voidwalker"); // no soulstones
        engine->DoNextAction(NULL);

        ai->spellCooldowns.remove("summon voidwalker"); // no soulstones
        engine->DoNextAction(NULL);
        ai->hasPet = TRUE;

        engine->DoNextAction(NULL);

        std::cout << ai->buffer;
        CPPUNIT_ASSERT(!strcmp(ai->buffer.c_str(), ">drain soul>summon voidwalker>immolate"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( FrostWarlockTestCase );
