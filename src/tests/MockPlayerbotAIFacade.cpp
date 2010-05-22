#include "pch.h"
#include "MockPlayerbotAIFacade.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

void MockPlayerbotAIFacade::Attack(Unit* target)
{
    if (target == MockedTargets::GetLeastThreat())
        buffer.append(">attack least threat");

    if (target == MockedTargets::GetBiggerThreat())
        buffer.append(">attack bigger threat");
}