#include "pchdef.h"
#include "FleeManager.h"

using namespace ai;
using namespace std;

void FleeManager::calculateDistanceToPlayers(FleePoint *point) {
	Group* group = bot->GetGroup();
	if (!group)
		return;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) {
		Player* player = gref->getSource();
		if(player == bot)
			continue;

		float d = player->GetDistance(point->x, point->y, point->z);
		point->toAllPlayers.probe(d);
		switch (player->getClass()) {
			case CLASS_HUNTER:
			case CLASS_MAGE:
			case CLASS_PRIEST:
			case CLASS_WARLOCK:
				point->toRangedPlayers.probe(d);
				break;
			case CLASS_PALADIN:
			case CLASS_ROGUE:
			case CLASS_WARRIOR:
				point->toMeleePlayers.probe(d);
				break;
		}
	}
}

void FleeManager::calculateDistanceToCreatures(FleePoint *point) {
	RangePair &distance = point->toCreatures;

	float botAngle = bot->GetOrientation();
	for (map<Unit*, ThreatManager*>::iterator i = attackers->begin(); i!=attackers->end(); i++) {  
		Unit* unit = i->first;

		float d = unit->GetDistance(point->x, point->y, point->z);
		distance.probe(d);
	}
}

void FleeManager::calculatePoints(list<FleePoint*> &points) {
	float botPosX = bot->GetPositionX();
	float botPosY = bot->GetPositionY();
	float botPosZ = bot->GetPositionZ();

	for (float r = maxAllowedDistance; r>=15.0f; r -= 10.0f) {
		for (float angle = -M_PI + followAngle; angle < M_PI + followAngle; angle += M_PI / 8) {
			float x = botPosX + cos(angle) * r;
			float y = botPosY + sin(angle) * r;

			if (!bot->IsWithinLOS(x, y, botPosZ))
				continue;

			FleePoint *point = new FleePoint(x, y, botPosZ);
			calculateDistanceToPlayers(point);
			calculateDistanceToCreatures(point);
			points.push_back(point);
		}
	}
}

void FleeManager::deletePoints(list<FleePoint*> &points) {
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++) {
		FleePoint* point = *i;
		delete point;
	}
	points.clear();
}

bool FleeManager::isAllowed(FleePoint* point) {
	return point->toAllPlayers.max <= 30.0f && point->toAllPlayers.min >= 5.0f &&
		point->toCreatures.min >= 15.0f;
}

bool FleeManager::isBetterThan(FleePoint* point, FleePoint* compareTo) {
	return (point->toCreatures.min - compareTo->toCreatures.min) > 1.0f &&
		(point->toMeleePlayers.min - compareTo->toMeleePlayers.min) < 1.0f &&
		(point->toRangedPlayers.min - compareTo->toRangedPlayers.min) > 1.0f;
}

FleePoint* FleeManager::selectOptimalPoint(list<FleePoint*> &points) {
	FleePoint* selected = NULL;
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++) {
		FleePoint* point = *i;
		if (isAllowed(point) && (!selected || isBetterThan(selected, point)))
			selected = point;
	}
	return selected;
}

bool FleeManager::flee(float* rx, float* ry, float* rz) {
	list<FleePoint*> points;
	bool result = false;
	calculatePoints(points);

	FleePoint* point = selectOptimalPoint(points);
	if (point) {
		*rx = point->x;
		*ry = point->y;
		*rz = bot->GetPositionZ();
		result = true;
	}
	
	deletePoints(points);
	return result;
}
