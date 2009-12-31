#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidActions.h"

using namespace ai;

BOOL DruidLowHealthTrigger::IsActive() { return LowHealthTrigger::IsActive(); }