#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "LfgActions.h"
#include "../../AiFactory.h"
#include "../../PlayerbotAIConfig.h"
#include "../ItemVisitors.h"

using namespace ai;

bool LfgJoinAction::Execute(Event event)
{
    if (!sPlayerbotAIConfig.randomBotJoinLfg)
        return false;

    if (bot->isDead())
        return false;

    if (!master)
        return false;

    if (!master->GetRandomPlayerbotMgr()->IsRandomBot(bot))
        return false;

    if (ai->GetSecurity()->LevelFor(master) < PLAYERBOT_SECURITY_INVITE)
        return false;

    if (abs((int)master->getLevel() - (int)bot->getLevel()) > 2)
        return false;

    int botGS = (int)bot->GetEquipGearScore(false, false);
    int masterGS = (int)master->GetEquipGearScore(false, false);
    if (masterGS && bot->getLevel() > 15 && 100 * (masterGS - botGS) / masterGS >= (20 + (91 - (int)master->getLevel()) / 4))
        return false;

    if (sLFGMgr.GetQueueInfo(bot->GetObjectGuid()))
        return false;

    return JoinProposal();
}

bool LfgJoinAction::SetRoles()
{
    LFGPlayerState* state = bot->GetLFGPlayerState();
    if (!state)
        return false;

    state->SetRoles(LFG_ROLE_MASK_DAMAGE);

    int spec = AiFactory::GetPlayerSpecTab(bot);
    switch (bot->getClass())
    {
    case CLASS_DRUID:
        if (spec == 2)
            state->SetRoles(LFG_ROLE_MASK_HEALER);
        break;
    case CLASS_PALADIN:
        if (spec == 1)
            state->SetRoles(LFG_ROLE_MASK_TANK);
        if (spec == 0)
            state->SetRoles(LFG_ROLE_MASK_HEALER);
        break;
    case CLASS_PRIEST:
        if (spec != 2)
            state->SetRoles(LFG_ROLE_MASK_HEALER);
        break;
    case CLASS_SHAMAN:
        if (spec == 2)
            state->SetRoles(LFG_ROLE_MASK_HEALER);
        break;
    case CLASS_WARRIOR:
        if (spec == 2)
            state->SetRoles(LFG_ROLE_MASK_TANK);
        break;
    }
}

bool LfgJoinAction::JoinProposal()
{
    LFGPlayerState* state = bot->GetLFGPlayerState();
    if (!state)
        return false;

    if (!SetRoles())
        return false;

    ItemCountByQuality visitor;
    IterateItems(&visitor, ITERATE_ITEMS_IN_EQUIP);
	bool heroic = visitor.count[ITEM_QUALITY_EPIC] >= 3 && bot->getLevel() >= 70;
    bool random = urand(0, 100) < 50;

    LFGDungeonSet list;
    for (uint32 i = 0; i < sLFGDungeonStore.GetNumRows(); ++i)
    {
        LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(i);
        if (!dungeon || (dungeon->type != LFG_TYPE_RANDOM_DUNGEON && dungeon->type != LFG_TYPE_DUNGEON && dungeon->type != LFG_TYPE_HEROIC_DUNGEON))
            continue;

        if (dungeon->recminlevel && (int)dungeon->recminlevel > (int)bot->getLevel())
            continue;

        if ((int)bot->getLevel() > (int)dungeon->maxlevel)
            continue;

        if (heroic && !dungeon->difficulty)
            continue;

        list.insert(dungeon);
    }

    if (random)
	{
		sLog.outBasic("Bot %s joined to LFG_TYPE_RANDOM_DUNGEON", bot->GetName());
        state->SetType(LFG_TYPE_RANDOM_DUNGEON);
	}
    else if (heroic)
	{
		sLog.outBasic("Bot %s joined to LFG_TYPE_HEROIC_DUNGEON", bot->GetName());
        state->SetType(LFG_TYPE_HEROIC_DUNGEON);
	}
    else
	{
		sLog.outBasic("Bot %s joined to LFG_TYPE_DUNGEON", bot->GetName());
        state->SetType(LFG_TYPE_DUNGEON);
	}

    state->SetComment("bot");
    state->SetDungeons(list);

    sLFGMgr.Join(bot);
    return true;
}

bool LfgRoleCheckAction::Execute(Event event)
{
    Group* group = bot->GetGroup();
    if (group)
    {
        if (!SetRoles())
            return false;

        sLFGMgr.UpdateRoleCheck(group);
        return true;
    }

    return false;
}

bool LfgAcceptAction::Execute(Event event)
{
    WorldPacket p(event.getPacket());

    uint32 dungeon;
    uint8 state;
    uint32 id;
    p >> dungeon >> state >> id;

    sLFGMgr.UpdateProposal(id, bot->GetObjectGuid(), true);
    return true;
}

bool LfgLeaveAction::Execute(Event event)
{
    if (!sLFGMgr.GetQueueInfo(bot->GetObjectGuid()))
        return false;

    sLFGMgr.Leave(bot);
	return true;
}
