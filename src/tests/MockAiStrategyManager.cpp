#include "pch.h"
#include "aitest.h"
#include "MockAiStrategyManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

void MockAiStrategyManager::ChangeStrategy(const char* type, const char* name)
{
    buffer->append(">").append(type).append(":").append(name);
}
