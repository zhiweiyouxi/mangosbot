#pragma once

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

#include <stdio.h>
#include <iostream>

#include <list>
#include "Platform/Define.h"

#include <stdexcept>

#define GLOBAL_COOLDOWN 2
#define BOT_REACT_DELAY 1

#define BOTLOOT_DISTANCE 25.0f
#define EAT_DRINK_PERCENT 40
#define SPELL_DISTANCE 25.0f
#define BOT_REACT_DISTANCE 50.0f
