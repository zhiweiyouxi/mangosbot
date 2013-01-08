#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WhoAction.h"
#include "../../AiFactory.h"
#include "../ItemVisitors.h"

using namespace ai;



bool WhoAction::Execute(Event event)
{
    Player* owner = event.getOwner();
    if (!owner)
        return false;

    ostringstream out;

    int spec = AiFactory::GetPlayerSpecTab(bot);
    out << "|h|cffffffff" << chat->formatClass(bot, spec);
    out << "|h|cff00ff00 (" << bot->getLevel() << "|h|cffffffff lvl), ";

    ItemCountByQuality visitor;
    IterateItems(&visitor, ITERATE_ITEMS_IN_EQUIP);

    bool needSlash = false;
    if (visitor.count[ITEM_QUALITY_EPIC])
    {
        out << "|h|cffff00ff" << visitor.count[ITEM_QUALITY_EPIC] << "|h|cffffffff";
        needSlash = true;
    }

    if (visitor.count[ITEM_QUALITY_RARE])
    {
        if (needSlash) out << "/";
        out << "|h|cff8080ff" << visitor.count[ITEM_QUALITY_RARE] << "|h|cffffffff";
        needSlash = true;
    }

    if (visitor.count[ITEM_QUALITY_UNCOMMON])
    {
        if (needSlash) out << "/";
        out << "|h|cff00ff00" << visitor.count[ITEM_QUALITY_UNCOMMON] << "|h|cffffffff";
        needSlash = true;
    }

    if (needSlash)
    {
        out << " gear (|h|cff00ff00" << bot->GetEquipGearScore(false, false) << "|h|cffffffff GS)";
    }

    Player* master = GetMaster();
    Group* group = master ? master->GetGroup() : bot->GetGroup();
    if (group)
    {
        out << " in " << (int)group->GetMembersCount() <<  "-party with (";
        int index = 1, followIndex = -1;
        for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            Player* player = ref->getSource();
            if (!player)
                out << "?";
            else if (player == master)
                out << "!" << player->GetName() << "!";
            else
                out << player->GetName();

            if (ref->next())
                out << ", ";

            if(ref->getSource() == master)
                continue;

            if(ref->getSource() == bot)
                followIndex = index;

            index++;
        }
        out << ") " << followIndex << "th";
    }

    // ignore random bot chat filter
    WorldPacket data(SMSG_MESSAGECHAT, 1024);
    bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, out.str(), LANG_UNIVERSAL);
    owner->GetSession()->SendPacket(&data);
    return true;
}
