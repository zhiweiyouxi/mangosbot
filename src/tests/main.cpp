#include "Common.h"
#include "Language.h"
#include "Log.h"
#include "World.h"
#include "ScriptCalls.h"
#include "ObjectMgr.h"
#include "WorldSession.h"
#include "Config/ConfigEnv.h"
#include "Util.h"
#include "AccountMgr.h"
#include "CliRunnable.h"
#include "MapManager.h"
#include "Player.h"
#include "Chat.h"
#include "Database/DatabaseEnv.h"
#include "Config/ConfigEnv.h"
#include "Log.h"
#include "Master.h"
#include "SystemConfig.h"
#include "revision.h"
#include "revision_nr.h"
#include <openssl/opensslv.h>
#include <openssl/crypto.h>
#include <ace/Version.h>

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

DatabaseType WorldDatabase;                                 ///< Accessor to the world database
DatabaseType CharacterDatabase;                             ///< Accessor to the character database
DatabaseType loginDatabase;                                 ///< Accessor to the realm/login database
uint32 realmID;                                             ///< Id of the realm

bool ChatHandler::HandleAccountDeleteCommand(const char* args)
{
    return true;
}

bool ChatHandler::HandleCharacterDeleteCommand(const char* args)
{
    return true;
}

bool ChatHandler::HandleServerExitCommand(const char* /*args*/)
{
    return true;
}

bool ChatHandler::HandleAccountOnlineListCommand(const char* /*args*/)
{
    return true;
}

bool ChatHandler::HandleAccountCreateCommand(const char* args)
{
    return true;
}

bool ChatHandler::HandleServerSetLogLevelCommand(const char *args)
{
    return true;
}
void CliRunnable::run()
{
}


int main()
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}