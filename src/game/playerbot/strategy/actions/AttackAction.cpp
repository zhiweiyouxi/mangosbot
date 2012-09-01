#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "AttackAction.h"
#include "../../../MovementGenerator.h"
#include "../../../CreatureAI.h"
#include "../../LootObjectStack.h"

using namespace ai;

bool AttackAction::Execute(Event event)
{
    Unit* target = GetTarget();

    if (!target)
        return false;

    return Attack(target);
}

bool AttackMyTargetAction::Execute(Event event)
{

    ObjectGuid guid = master->GetSelectionGuid();
    if (!guid)
        return false;

    return Attack(ai->GetCreature(guid));
}

bool AttackAction::Attack(Unit* target)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm.GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return false;

    if (!target)
        return false;

    if (bot->IsFriendlyTo(target))
    {
        ai->TellMaster("Target is friendly");
        return false;
    }
    if (!bot->IsWithinLOSInMap(target))
    {
        ai->TellMaster(LOG_LVL_DEBUG, "Target is not in my sight");
        return false;
    }

    if (bot->IsMounted())
    {
        WorldPacket emptyPacket;
        bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
    }

    ObjectGuid guid = target->GetObjectGuid();
    bot->SetSelectionGuid(target->GetObjectGuid());

    Unit* oldTarget = context->GetValue<Unit*>("current target")->Get();
    context->GetValue<Unit*>("old target")->Set(oldTarget);

    context->GetValue<Unit*>("current target")->Set(target);
    context->GetValue<LootObjectStack*>("available loot")->Get()->Add(guid);

    Pet* pet = bot->GetPet();
    if (pet)
    {
        CreatureAI* creatureAI = ((Creature*)pet)->AI();
        if (creatureAI)
            creatureAI->AttackStart(target);
    }

    bot->Attack(target, true);
    return true;
}
