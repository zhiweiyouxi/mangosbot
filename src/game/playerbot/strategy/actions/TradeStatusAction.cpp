#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "TradeStatusAction.h"

#include "../ItemVisitors.h"

using namespace ai;



bool TradeStatusAction::Execute(Event event)
{
    if (!bot->GetTrader())
        return false;

    WorldPacket p(event.getPacket());
    p.rpos(0);
    uint32 status;
    p >> status;

    if (status == TRADE_STATUS_TRADE_ACCEPT)
    {
        WorldPacket p;
        uint32 status = 0;
        p << status;
        bot->GetSession()->HandleAcceptTradeOpcode(p);
        return true;
    }
    else if (status == TRADE_STATUS_BEGIN_TRADE)
    {
        BeginTrade();
        return true;
    }
    
    return false;
}


void TradeStatusAction::BeginTrade()
{
    WorldPacket p;
    bot->GetSession()->HandleBeginTradeOpcode(p);

    ListItemsVisitor visitor;
    IterateItems(&visitor);

    ai->TellMaster("=== Trade ===");
    TellItems(visitor.items);
}

