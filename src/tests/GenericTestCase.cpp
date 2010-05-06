#include "pch.h"

#include "EngineTestBase.h"
#include "../game/DruidActionFactory.h"

using namespace ai;

class GenericTestCase : public EngineTestBase
{
    CPPUNIT_TEST_SUITE( GenericTestCase );
    CPPUNIT_TEST( healthstone );
	CPPUNIT_TEST( flee );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
		EngineTestBase::setUp();
		setupEngine(new DruidActionFactory(ai), "bear", NULL);
    }

protected:
    void healthstone()
    {
		itemAvailable("healthstone", 1);
        
		lowHealth(1);
		lowMana(1);
        tick(); 

        assertActions(">healthstone");
    }
	void flee()
	{
		lowHealth(1);
		lowMana(1);
		tick(); 

		assertActions(">flee");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( GenericTestCase );
