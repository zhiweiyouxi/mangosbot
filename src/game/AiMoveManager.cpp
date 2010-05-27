#include "pchdef.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "AiSocialManager.h"
#include "AiInventoryManager.h"
#include "AiMoveManager.h"
#include "MotionMaster.h"
#include "FleeManager.h"
#include "AiManagerRegistry.h"
#include "SpellAuras.h"

using namespace ai;
using namespace std;

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
	Stay();
	bot->GetMotionMaster()->MoveFollow(target, distance, GetFollowAngle()); 	
}

bool AiMoveManager::Flee(Unit* target, float distance)
{
	std::list<ThreatManager*> attackers;
	aiRegistry->GetStatsManager()->findAllAttackers(attackers);

	FleeManager manager(bot, &attackers, distance, GetFollowAngle());

	float rx, ry, rz;
	if (manager.flee(&rx, &ry, &rz)) {
		Stay();
		bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
		return true;
	}
	return false;
}

void AiMoveManager::Stay()
{
	bot->GetMotionMaster()->Clear( true );
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
	bot->SetSelection(0);
}

void AiMoveManager::Summon()
{
    Player* master = ai->GetMaster();
    if (!bot->IsWithinDistInMap( master, 50, true ))
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

