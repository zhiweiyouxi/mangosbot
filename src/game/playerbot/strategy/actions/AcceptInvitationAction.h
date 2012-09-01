#pragma once

#include "../Action.h"

namespace ai
{
    class AcceptInvitationAction : public Action {
    public:
        AcceptInvitationAction(PlayerbotAI* ai) : Action(ai, "accept invitation") {}

        virtual bool Execute(Event event)
        {
            Group* grp = bot->GetGroupInvite();
            if (!grp)
                return false;

            Player* inviter = sObjectMgr.GetPlayer(grp->GetLeaderGuid());
            if (!inviter)
                return false;

            if (inviter != master) {
                return false;
            }

            if ((int)bot->getLevel() - (int)inviter->getLevel() > 5 && master->GetRandomPlayerbotMgr()->IsRandomBot(bot)) {
                ai->TellMaster("You are too low-level to invite me");
                return false;
            }

            WorldPacket p;
            uint32 roles_mask = 0;
            p << roles_mask;
            bot->GetSession()->HandleGroupAcceptOpcode(p);

            return true;
        }
    };

}
