#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PossibleTargetsValue.h"

#include "../../../../game/GridNotifiers.h"
#include "../../../../game/GridNotifiersImpl.h"
#include "../../../../game/CellImpl.h"

using namespace ai;
using namespace MaNGOS;

void PossibleTargetsValue::FindUnits(list<Unit*> &targets)
{
    MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, range);
    MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
    Cell::VisitAllObjects(bot, searcher, range);
}

bool PossibleTargetsValue::AcceptUnit(Unit* unit)
{
    return !unit->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) &&
            (unit->IsHostileTo(bot) || (unit->getLevel() > 1 && !unit->IsFriendlyTo(bot)));
}
