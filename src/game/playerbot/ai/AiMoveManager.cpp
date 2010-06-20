#include "../../pchdef.h"
#include "../playerbot.h"
#include "../../MotionMaster.h"
#include "../../MovementGenerator.h"

#include "FleeManager.h"

using namespace ai;
using namespace std;

AiMoveManager::AiMoveManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
    taxiMaster = 0;
}

float AiMoveManager::GetDistanceTo(Unit* target)
{
	return target ? bot->GetDistance(target) : 0.0f; 
}

void AiMoveManager::MoveTo(Unit* target, float distance)
{
	Follow(target, distance);
}

float AiMoveManager::GetFollowAngle()
{
	Group* group = bot->GetGroup();
	if (!group)
		return 0.0f;

	GroupReference *gref = group->GetFirstMember();
	int index = 0;
	while( gref )
	{
		if( gref->getSource() == bot)
		{
			return M_PI / group->GetMembersCount() * index;
		}
		gref = gref->next();
		index++;
	}
	return 0;
}

void AiMoveManager::Follow(Unit* target, float distance)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return;

    if (bot->GetDistance(target) > BOT_REACT_DISTANCE)
    {
        Stay();
        return;
    }

	mm.MoveFollow(target, distance, GetFollowAngle());
    ai->SetNextCheckDelay(GLOBAL_COOLDOWN);
}

void AiMoveManager::MoveTo(uint32 mapId, float x, float y, float z)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return;

    if (bot->GetMapId() != mapId || bot->GetDistance(x, y, z) > BOT_REACT_DISTANCE)
    {
        Stay();
        return;
    }

    mm.MovePoint(mapId, x, y, z);
    ai->SetNextCheckDelay(GLOBAL_COOLDOWN);
}

bool AiMoveManager::Flee(Unit* target, float distance)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return false;

    if (!target)
        return false;

    if (bot->GetDistance(target) > BOT_REACT_DISTANCE)
    {
        Stay();
        return false;
    }

    ai->SetNextCheckDelay(GLOBAL_COOLDOWN);

    if (bot->isFrozen() || bot->IsPolymorphed() || !bot->CanFreeMove())
        return false;
    
    AttackerMap attackers = bot->GetPlayerbotAI()->GetGroupStatsManager()->GetAttackers();
	FleeManager manager(bot, &attackers, distance, GetFollowAngle());
        
    float rx, ry, rz;
	if (!manager.CalculateDestination(&rx, &ry, &rz)) 
        return false;

    bot->UpdateGroundPositionZ(rx, ry, rz);
	bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
	return true;
}

void AiMoveManager::Stay()
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return;

	mm.Clear( true );
	bot->clearUnitState( UNIT_STAT_CHASE );
	bot->clearUnitState( UNIT_STAT_FOLLOW );

	if (!bot->IsStandState())
		bot->SetStandState(UNIT_STAND_STATE_STAND);
}

bool AiMoveManager::IsMoving(Unit* target)
{
	return target && target->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE;
}

void AiMoveManager::Attack(Unit* target)
{
	if (!target) 
		return;

    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm->GetMovementGeneratorType() == FLIGHT_MOTION_TYPE)
        return;

	if (!bot->isInFrontInMap(target, 5.0f))
		bot->SetInFront(target);

	if (bot->getStandState() != UNIT_STAND_STATE_STAND)
		bot->SetStandState(UNIT_STAND_STATE_STAND);


	if (bot->IsFriendlyTo(target))
	{
		aiRegistry->GetSocialManager()->TellMaster("Target is friendly");
		return;
	}
	if (!bot->IsWithinLOSInMap(target))
	{
		aiRegistry->GetSocialManager()->TellMaster("Target is not in my sight, maybe later?");
		return;
	}

	uint64 guid = target->GetGUID();
	bot->SetSelection(guid);
	bot->Attack(target, true);

    aiRegistry->GetTargetManager()->SetCurrentTarget(target);
	aiRegistry->GetInventoryManager()->AddLoot(guid);
}

void AiMoveManager::ReleaseSpirit()
{
	if (bot->isAlive() || bot->GetCorpse())
		return;

	bot->SetBotDeathTimer();
	bot->BuildPlayerRepop();

	WorldLocation loc;
	Corpse *corpse = bot->GetCorpse();
	corpse->GetPosition( loc );
	bot->TeleportTo( loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, bot->GetOrientation() );
}

void AiMoveManager::Resurrect()
{
	aiRegistry->GetMoveManager()->Stay();
	Corpse* corpse = bot->GetCorpse();
	if (corpse)
	{
		time_t reclaimTime = corpse->GetGhostTime() + bot->GetCorpseReclaimDelay( corpse->GetType()==CORPSE_RESURRECTABLE_PVP );
		if (reclaimTime > time(0))
		{
			ostringstream os;
			os << "Will resurrect in ";
			os << (reclaimTime - time(0));
			os << " secs";
			aiRegistry->GetSocialManager()->TellMaster(os.str().c_str());
			ai->SetNextCheckDelay(reclaimTime - time(0));
		}
		else
			Revive();
	}
}

void AiMoveManager::Revive()
{
	PlayerbotChatHandler ch(ai->GetMaster());
	if (! ch.revive(*bot))
	{
		aiRegistry->GetSocialManager()->TellMaster(".. could not be revived ..");
		return;
	}
    aiRegistry->GetTargetManager()->SetCurrentTarget(NULL);
	bot->SetSelection(0);
}

void AiMoveManager::Summon()
{
    Player* master = ai->GetMaster();
    if (!bot->IsWithinDistInMap( master, BOT_REACT_DISTANCE, true ))
    {
        PlayerbotChatHandler ch(master);
        if (! ch.teleport(*bot))
        {
            ch.sysmessage(".. could not be teleported ..");
        }
    }
}

void AiMoveManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "attack")
	{
		Attack(ObjectAccessor::GetUnit(*bot, fromPlayer.GetSelection()));
	}
	else if(text == "release" && !bot->isAlive())
	{
		ReleaseSpirit();
	}
    else if(text == "fly" && taxiMaster)
    {
        bot->SetSelection(taxiMaster);

        Creature *npc = bot->GetNPCIfCanInteractWith(taxiMaster, UNIT_NPC_FLAG_FLIGHTMASTER);
        if (!npc)
        {
            aiRegistry->GetSocialManager()->TellMaster("Cannot talk to flightmaster");
            return;
        }

        if (!bot->ActivateTaxiPathTo(taxiNodes, npc))
            aiRegistry->GetSocialManager()->TellMaster("I can not fly with you");
    }
    else if (text == "reset")
    {
        bot->GetMotionMaster()->Clear();
        bot->m_taxi.ClearTaxiDestinations();
    }
}

void AiMoveManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
		// if a change in speed was detected for the master
		// make sure we have the same mount status
	case SMSG_FORCE_RUN_SPEED_CHANGE:
		{
			WorldPacket p(packet);
			uint64 guid = extractGuid(p);
			Player* master = ai->GetMaster();
			if (guid != master->GetGUID())
				return;
			if (master->IsMounted() && !bot->IsMounted())
			{
				if (!master->GetAurasByType(SPELL_AURA_MOUNTED).empty())
				{
					int32 master_speed1 = 0;
					int32 master_speed2 = 0;
					master_speed1 = ai->GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[1];
					master_speed2 = ai->GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[2];

					aiRegistry->GetSpellManager()->Mount(master_speed1, master_speed2);
				}
			}
			else if (!master->IsMounted() && bot->IsMounted())
			{
				aiRegistry->GetSpellManager()->Unmount();
			}
			return;
		}

		// handle flying acknowledgement
	case SMSG_MOVE_SET_CAN_FLY:
		{
			WorldPacket p(packet);
			uint64 guid = extractGuid(p);
			if (guid != bot->GetGUID())
				return;
			bot->m_movementInfo.AddMovementFlag(MOVEMENTFLAG_FLYING2);
			//bot->SetSpeed(MOVE_RUN, GetMaster()->GetSpeed(MOVE_FLIGHT) +0.1f, true);
			return;
		}

		// handle dismount flying acknowledgement
	case SMSG_MOVE_UNSET_CAN_FLY:
		{
			WorldPacket p(packet);
			uint64 guid = extractGuid(p);
			if (guid != bot->GetGUID())
				return;
			bot->m_movementInfo.RemoveMovementFlag(MOVEMENTFLAG_FLYING2);
			//bot->SetSpeed(MOVE_RUN,GetMaster()->GetSpeedRate(MOVE_RUN),true);
			return;
		}

	case SMSG_RESURRECT_REQUEST:
		{
			aiRegistry->GetMoveManager()->Revive();
			return;
		}
	}

}

void AiMoveManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
    case CMSG_ACTIVATETAXI:
        WorldPacket p(packet);
        p.rpos(0);
        
        taxiNodes.clear();
        taxiNodes.resize(2);

        p >> taxiMaster >> taxiNodes[0] >> taxiNodes[1];
        return;
    }   
}