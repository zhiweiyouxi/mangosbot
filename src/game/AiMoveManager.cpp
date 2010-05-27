#include "pchdef.h"
#include "AiMoveManager.h"
#include "MotionMaster.h"
#include "FleeManager.h"
#include "AiManagerRegistry.h"

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
