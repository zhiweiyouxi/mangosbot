#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

BOOL HunterEnemyTooCloseTrigger::IsActive() { return EnemyTooCloseTrigger::IsActive(); }