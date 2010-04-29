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

protected:
	virtual void setupEngine(ActionFactory* actionFactory, ...)
	{
        engine = new Engine(ai, actionFactory);
        
		va_list vl;
		va_start(vl, actionFactory);

		const char* cur = NULL;
		do 
		{
			cur = va_arg(vl, const char*);
			if (cur)
				engine->addStrategy(cur);
		}
		while (cur);

		va_end(vl);
        
		engine->Init();
    }

protected:
    MockPlayerbotAIFacade *ai;
    Engine *engine;
};
