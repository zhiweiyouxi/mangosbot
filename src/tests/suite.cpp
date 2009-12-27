#include <stdio.h>
#include <iostream>

#include <list>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestPath.h>
#include <stdexcept>

#include "../game/AiAction.h"
#include "../game/AiActionBasket.h"
#include "../game/AiQueue.h"

class AiTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( AiTestCase );
  CPPUNIT_TEST( queueTest );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp()
	{
	}

protected:
	void queueTest()
	{
		AiAction action1;
		AiAction action2;
		AiAction action3;

		AiQueue q;
		q.Push(&action1, 0.5f);
		q.Push(&action2, 0.7f);
		q.Push(&action3, 0.3f);
		
		
		CPPUNIT_ASSERT(q.Pop() == &action2);
		CPPUNIT_ASSERT(q.Pop() == &action1);
		CPPUNIT_ASSERT(q.Pop() == &action3);
		CPPUNIT_ASSERT(q.Pop() == NULL);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( AiTestCase );
